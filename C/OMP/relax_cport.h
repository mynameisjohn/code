#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#define NUM_THREADS 8
#define CHUNK 40

typedef struct problem_defs{
  //Arrays containing the bc's and image
  int ** inside;
  //voltage array
  float **v, **vN;
  //increment variables
  int size,img,nstp,nimg,npr,step,npointsin;
  //data file
  FILE *output;
} problem_defs;

//extern int pxa[250000];
extern unsigned char initialized;

int min(int v, int m){
   return (v<m) ? v : m;
}

int max(int v, int M){
   return (v>M) ? v : M;
}

int clamp (int v, int m, int M){
   return max(min(v,M),m);
}

//Functions for creating 2-D arrays
unsigned char ** make2Duchar(int w, int h){
  int i,j;
  unsigned char ** result = (unsigned char **) malloc(w*sizeof(unsigned char));
  for (i=0;i<w;i++)
    result[i]=(unsigned char *)malloc(h*sizeof(unsigned char));
  return result;
}

float ** make2Dfloat(int w, int h){
  int i,j;
  float ** result = (float **) malloc(h*sizeof(float*));
  for (i=0;i<h;i++)
    result[i]=(float *)malloc(w*sizeof(float));
  for (i=0;i<h;i++)
    for (j=0;j<w;j++)
      result[i][j]=(float)0;
  return result;
}

int ** make2Dint(int w, int h){
  int i,j;
  int ** result = (int **) malloc(h*sizeof(int*));
  for (i=0;i<h;i++)
    result[i]=(int *)malloc(w*sizeof(int));
  for (i=0;i<h;i++)
    for (j=0;j<w;j++)
      result[i][j]=(int)1;
  return result;
}

//Initialize the boundary conditions
int init(float ** v, int ** inside, int sizeX,int sizeY){
  int x,y;
  float x0=(float)0.25, x1=(float)0.75, y0=(float)0.25, y1=(float)0.75,
    xc=(float)0.5, yc=(float)0.35, r=(float)0.125, xd=(float)0.35;
  float v1,v2,v3,v4,v5,v6,xa,ya;

  printf("Inside init\n");

  printf("Potential of the circle = 20\n");
  v1=2000000;
  printf("Potential of the rectangle = -20\n");
  v2=0;
  printf("Potential of the top boundary = -10\n");
  v3=20;
  printf("Potential of the right boundary = 0\n");
  v4=-20;
  printf("Potential of the bottom boundary = 10\n");
  v5=20;
  printf("Potential of the left boundary = 0\n");
  v6=-20;
  
  
  for (y=0;y<sizeY;y++){
    ya=((float)y)/((float)sizeY);
    for (x=0;x<sizeX;x++){
      xa=((float)x)/((float)sizeX);
      if (y==0){
	v[y][x]=v5;
	inside[y][x]=0;
      }
      if (y==sizeY-1){
	v[y][x]=v3;
	inside[y][x]=0;
      }
      if (x==0){
	v[y][x]=v6;
	inside[y][x]=0;
      }
      if (x==sizeX-1){
	v[y][x]=v4;
	inside[y][x]=0;
	}/*
      if (x0<=xa && xa<=x1 && y0<=ya && ya<=y1){
	v[y][x]=v2;
	inside[y][x]=0;
      }*/
      if (pow((xa-xc),2)+pow((ya-yc),2)<=r*r){
	v[y][x]=v1;
	inside[y][x]=0;
      }/*
      if (pow((xa-xd),2)+pow((ya-yc),2)<=r*r){
	v[y][x]=v1;
	inside[y][x]=0;
      }*/
    }
  }

  return 1;
}

int v2pxa(int * pxa, float ** v, int ** inside, int sizeX, int sizeY){
  int x,y; 
  
#pragma omp parallel for shared(pxa,v,inside) private (x,y)
  for (y=0;y<sizeY;y++){
    for (x=0;x<sizeX;x++){
      int r,g,b; float t;

      t=(5*(M_PI/(float)2-atan(v[y][x])))/(float)3;
      r = 128*(2*cos(t)+1);
      if (r<0) r=0; if (r>255) r=255;
      g = 128*(2*cos(t-((float)2)*M_PI/((float)3))+1);
      if (g<0) g=0; if (g>255) g=255;
      b = 128*(2*cos(t+((float)2)*M_PI/(float)3)+1);
      if (b<0) b=0; if (b>255) b=255;
      if (inside[y][x])
	pxa[y*sizeY+x]=b+(g<<8)+(r<<16);
      else
	pxa[y*sizeY+x]=0;
    }
  }
  
  return 1;
}

int count (int ** inside, int w, int h){
  int c=0,i,j;
  for (i=0;i<h;i++){
    for (j=0;j<w;j++){
      c+=(inside[i][j]&0x1);
      //printf("%d ",inside[i][j]);
    }
    //  printf("\n");
  }
  return c;
}

void relax(int *pxa, int *xW, int *yW){
  int i,x,y;
  float r;
  //static problem_defs pDefs;
  static float ** v, ** vN, runtime;
  static int ** inside;
  static int step,sizeX,sizeY,nimg,nstp,npr,img,npointsin;

  if (!initialized)
    {
      //omp_set_num_threads(NUM_THREADS);
      initialized=1;
      runtime=omp_get_wtime();
      printf("Enter the grid dimensions (<500): ");
      scanf("%d",&sizeX);
      scanf("%d",&sizeY); 
      printf("\n");
      int NP;
      printf("Enter the number of threads you'd like to open (<=%d): ",
	omp_get_max_threads());
      scanf("%d",&NP);
      omp_set_num_threads(clamp(NP,1,omp_get_max_threads()));
      printf("\n");      

      v=make2Dfloat(sizeX,sizeY);
      vN=make2Dfloat(sizeX,sizeY);
      inside=make2Dint(sizeX,sizeY);
      *xW=sizeX;*yW=sizeY;
      //output=fopen("gs_data.out","w");

      init(v,inside,sizeX,sizeY);
      npointsin=count(inside,sizeX,sizeY);
      printf("%d\n",npointsin);
      img=0; step=0; nimg=0;
      
      r=0;
  
      for (y=1;y<sizeY-1;y++)
	for (x=1;x<sizeX-1;x++)
	  if (inside[y][x]){
	    float tmp = v[y][x];
	    v[y][x]=0.25*
	      (v[y+1][x]+v[y-1][x]+v[y][x+1]+v[y][x-1]);

	    r += (tmp-v[y][x])*(tmp-v[y][x]);
	  }
      printf("\n Total number of steps: %d, residue %lf.Runtime of %lf. \n",
	     step,r,omp_get_wtime()-runtime);
    }
  
  if (img==1)
    {
      printf("Enter the number of images, relaxation steps, and images per print: ");
      scanf("%d",&(nimg));
      scanf("%d",&(nstp));
      scanf("%d",&(npr));
      printf("\n");
    }
  
  //If we are in a position to iterate
  if (img>0 && img<=nimg)
    {//We iterate nstp steps per image
      for (i=0;i<nstp;i++)
	{
	  //Parallel region using red-black scheme
#pragma omp parallel shared(v,inside) private(x,y)
	  {   
#pragma omp for
	    for (y=1;y<sizeY-1;y++)
	      for (x=1;x<sizeX-1;x+=2)
		if (inside[y][x])
		  v[y][x]=0.25*
		    (v[y+1][x]+v[y-1][x]+v[y][x+1]+v[y][x-1]); 
#pragma omp for 
	  for (y=1;y<sizeY-1;y++)
	    for (x=2;x<sizeX-1;x+=2)
	      if (inside[y][x])
		v[y][x]=0.25*
		  (v[y+1][x]+v[y-1][x]+v[y][x+1]+v[y][x-1]);
	  }
	  //End of parallel region 
	step++;
      }
    }
  
  //Update our image
  v2pxa(pxa,v,inside,sizeX,sizeY);   
  
  //If we are in a position to print
  if (img>0 && (img%npr)==0 && img <= nimg){
    //Calculate the residue (and perform one iteration)
    r=0;/*
    for (y=1;y<size-1;y++)
      for (x=1;x<size-1;x++)
	if (inside[y][x]){
	  float tmp = v[y][x];
	  v[y][x]=0.25*
	    (v[y+1][x]+v[y-1][x]+v[y][x+1]+v[y][x-1]);
	  r += (tmp-v[y][x])*(tmp-v[y][x]);
	}
	*/
#pragma omp parallel shared(v,inside) private(x,y)
    {
#pragma omp for reduction(+:r)
    for (y=1;y<sizeY-1;y++)
      for (x=1;x<sizeX-1;x+=2)
	if (inside[y][x]){
	  float tmp = v[y][x];
	  v[y][x]=0.25*
	    (v[y+1][x]+v[y-1][x]+v[y][x+1]+v[y][x-1]);
	  r += (tmp-v[y][x])*(tmp-v[y][x]);
	}
#pragma omp for reduction(+:r)
    for (y=1;y<sizeY-1;y++)
      for (x=2;x<sizeX-1;x+=2)
	if (inside[y][x]){
	  float tmp = v[y][x];
	  v[y][x]=0.25*
	    (v[y+1][x]+v[y-1][x]+v[y][x+1]+v[y][x-1]);
	  r += (tmp-v[y][x])*(tmp-v[y][x]);
	}
    }
    //Print info
    printf("\n Total number of steps: %d, residue %lf, runtime of %lf\n",step,r,omp_get_wtime()-runtime);
  }

  //If we've hit our limit
  if (img==nimg){
    //fclose(output);
    printf("\n Close the window to stop the program. %d steps\n",step);
  }
  img++;
}
