#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <mpi.h>

#define DT 1
#define NPRE 1000
#define NPOST 200
#define NSPIKE 60
#define VTHRESH 350
#define VRESET -5
#define MASTER 0

/*
float MPI_HIST(float *invec, int *outvec, int *len, MPI_Dataype *dtype)
{
  int i,j,SIZE;
  MPI_Comm_size(MPI_COMM_WORLD,&SIZE);
  for (i=0;i<NPRE/(SIZE-1);i++)
      for (j=0;j<20;j++)
	outvec[((int)(invec[i*20+j]*100.0))/4]++;
}
*/
float max(float a, float b){
  return (a<b) ? b: a;
}

float min(float a, float b){
  return (a<b) ? a: b;
}

float clamp(float v, float m, float M){
  return max(min(v,M),m);
}

float solveRD(float x0, float a, float b){
  return x0*exp(-a*DT)+b;
}

int genData (int size, int rank, int *timings, float *weights, float v){
  int i, j, sSum, max=0;
  float R, lam, jitter;
  lam = (1/v)*1000.0;

  srand((unsigned)time(0));

  for (i=0;i<size;i++){
    sSum=0;
    for (j=0;j<NSPIKE;j++){
      R=rand()/(float)(RAND_MAX);
      sSum+=(int)(-1*lam*log(R));
      timings[i*NSPIKE+j]=sSum;
    }
    for (j=0;j<NPOST;j++){
      weights[i*NPOST+j]=rand()/(float)(RAND_MAX);
      // printf("%lf\n",weights[j]);
    }
    if (sSum>max) max = sSum;
  }
  //printf("%d\n",max);
  return max;
}

int jitter(int size, int *timings, int sigma, int rank){
  srand((unsigned)time(0)+rank);
  int i,j;
  float R1,R2, jit;
  for (i=0;i<size;i++)
    for (j=0;j<NSPIKE;j++){
      R1=rand()/(float)(RAND_MAX);
      R2=rand()/(float)(RAND_MAX);
      jit=sqrt(-2*log(R1))*cos(2*M_PI*R2);
      timings[i*NSPIKE+j]+=jit*sigma;
    }
}

int main(int argc, char *argv[]){
  FILE *output,*weightData;
  double start,end;

  int rank,size,localSize,i,j,time,tMax=0,tmp=0,count=0;
  float v=5.0,nu=0.2,mu=0.02,wMax=1.0,A=50.0/1000.0,B=1.0,C=0.0,D=20.0/1000.0;
  float Apost=25.0/1000.0,Cpost=1.0,tau,tauM=50.0,tauS=20.0,inhib;

  float *xCum=calloc(NPOST,sizeof(float)),*V=calloc(NPOST,sizeof(float));
  float *hostCum=malloc(NPOST*sizeof(float));
  
  int *weights=calloc(25,sizeof(int));
  int *weightBin=calloc(25,sizeof(int));//[25];
  //printf("%lf\n",clamp(2.0,0.0,1.0));

  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD,&size);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);

  MPI_Barrier(MPI_COMM_WORLD);
  start=MPI_Wtime();
  
  //Master picks up the slack
  localSize = NPRE/size+(rank==MASTER)*NPRE%size;

  float *dW=calloc(NPOST*localSize,sizeof(float)),*W=calloc(NPOST*localSize,sizeof(float));;
  float *xPre=calloc(localSize,sizeof(float)),x,y;
  float *xPost=calloc(NPOST,sizeof(float));
  int timings[localSize*NSPIKE];
  int sPre[localSize],sPost[NPOST];
  int *next=calloc(localSize,sizeof(int));

  tau = (tauM*tauS)/(tauM-tauS);
  
  //if (rank != MASTER){
  tmp=genData(localSize,rank,timings,W,v);
  jitter(localSize,timings,3,rank);
  for (i=0;i<localSize;i++)
    for (j=0;j<NPOST;j++)
      weightBin[((int)(W[NPOST*i+j]*100.0))/4]++;
  
  
  if (rank==MASTER)
    output = fopen("dat.out","w");
    
  
  /*
  for (i=0;i<localSize;i++)
    for (j=0;j<NPOST;j++)
      if (rank != MASTER) printf("%lf\n",W[i*NPOST+j]);
  */
  //printf("%d\n",tmp);
  MPI_Allreduce(&tmp,&tMax,1,MPI_INT,MPI_MAX,MPI_COMM_WORLD);
  
  if (rank==MASTER)
    printf("%d\n",tMax);
  
  //Now start the time loop
  
  for (time=0;time<tMax;time++){
    
    x=W[0];
    y=xPre[0];
    if (rank==1) MPI_Send(&x,1,MPI_FLOAT,MASTER,13,MPI_COMM_WORLD);
    if (rank==0) MPI_Recv(&x,1,MPI_FLOAT,1,13,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    if (rank==1) MPI_Send(&y,1,MPI_FLOAT,MASTER,13,MPI_COMM_WORLD);
    if (rank==0) MPI_Recv(&y,1,MPI_FLOAT,1,13,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    
    if (rank==MASTER)
      fprintf(output,"%d\t%lf\t%lf\t%lf\n",time,x,y,xPost[0]);

    for (j=0;j<NPOST;j++)
      xCum[j]=0;

    // if (rank != MASTER){
    for (i=0;i<localSize;i++){
	sPre[i]=(time==timings[i*NSPIKE+next[i]]);
	if (sPre[i]) next[i]++;
/*
      for (j=0;j<NSPIKE;j++){
	sPre[i] = (timings[i*NSPIKE+j] == time);
	if (sPre[i]) break;
      }*/
      for (j=0;j<NPOST;j++){
	dW[NPOST*i+j] = nu*(pow((1.0-W[i*NPOST+j]),mu)*xPre[i]*sPost[j] - pow(W[i*NPOST+j],mu)*xPost[j]*sPre[i]);
	//	  printf("%lf\n",dW[NPOST*i+j]);
      }
      xPre[i] = solveRD(xPre[i],A,sPre[i]*(B-C*xPre[i]));
      
      for (j=0;j<NPOST;j++){
	xCum[j] += xPre[i]*W[NPOST*i+j];
//	W[i*NPOST+j]=clamp((W[i*NPOST+j]+dW[i*NPOST+j]),(float)0,(float)1);
	}
    }
    // }
    
    MPI_Reduce(xCum,hostCum,NPOST,MPI_FLOAT,MPI_SUM,MASTER,MPI_COMM_WORLD);
    
    //if (rank!=MASTER){
    for (i=0;i<localSize;i++)
      for (j=0;j<NPOST;j++)
	W[i*NPOST+j]=clamp((W[i*NPOST+j]+dW[i*NPOST+j]),(float)0,(float)1);
    //MPI_Barrier(MPI_COMM_WORLD);
    // }
    if (rank==MASTER){
	inhib=0;
	for (i=0;i<NPOST;i++)
		inhib+=xPost[i];

      for (j=0;j<NPOST;j++){
//	inhib=0;
	inhib -= xPost[j];
	hostCum[j]*=2;
//	for (i=0;i<NPOST;i++)
//	  if (i!=j) inhib+=xPost[i];
	V[j]=solveRD(V[j],D,(hostCum[j]-inhib)*
		     tau*(solveRD(1,D,0)-solveRD(1,A,0)));
	sPost[j] = (V[j]>VTHRESH);
	if (sPost[j]){
	  V[j]=VRESET;
	  count++;
	}
	inhib += xPost[j];
      }
      for (j=0;j<NPOST;j++)
	xPost[j]=solveRD(xPost[j],Apost,
			 sPost[j]*(B-Cpost*xPost[j]));
      //MPI_Barrier(MPI_COMM_WORLD);
    }
    MPI_Bcast(sPost,NPOST,MPI_INT,MASTER,MPI_COMM_WORLD);
    MPI_Bcast(xPost,NPOST,MPI_FLOAT,MASTER,MPI_COMM_WORLD);
  }
  if (rank==MASTER) 
    fclose(output);
  
  
  for (i=0;i<localSize;i++)
    for (j=0;j<NPOST;j++){
      weights[((int)(W[NPOST*i+j]*100.0))/4]++;
      //	printf("%d\n",((int)W[NPOST*i+j]*100)/4);
    }
  
  
  MPI_Reduce(weights,weightBin,25,MPI_INT,MPI_SUM,MASTER,MPI_COMM_WORLD);
  
  if (rank==MASTER){
    weightData=fopen("weight.out","w");
    for (i=0;i<25;i++)
      fprintf(weightData,"%lf\t%d\n",((float)i*4.0)/100.0,weightBin[i]);
    fclose(weightData);
  }
  MPI_Barrier(MPI_COMM_WORLD);
  end=MPI_Wtime();
  
  if (rank==MASTER)
    printf("Runtime = %lf\n Count is %d\n", end-start,count/NPOST);
  
  MPI_Finalize();
  return 1;
}
