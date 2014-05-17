/* This is the graphics driver code for the program which implements
   the blurring of an image.  It calls the fortran subroutine blur_
   where the blurring, equivalent to a diffusion process, is done.

                            Copyright by Claudio Rebbi, January 2012 
*/

#include "relax_cport.h"
#include <stdio.h>
#include <string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#define WIDTH 800
#define HEIGHT 800

typedef struct problem_defs problem_defs;

int xwidth=WIDTH, ywidth=HEIGHT;
int xw[1], yw[1];
int pxa[WIDTH*HEIGHT];
unsigned char initialized=0;

extern void blur_(int *, int *, int *);

void display(void)
{
  float rp[2];
	//pDefs.img=0;
  relax(pxa,xw,yw);
//  printf("%x\n",pxa[10]);
  glClear(GL_COLOR_BUFFER_BIT);

  rp[0]=-((float)*xw)/xwidth; rp[1]=-((float)*yw)/ywidth;
  glRasterPos2fv(rp);
  glDrawPixels(*xw, *yw, GL_RGBA, GL_UNSIGNED_BYTE, pxa);

  glFlush(); 
  glutSwapBuffers();
}

void reshape(int w, int h)
{
  xwidth=w;
  ywidth=h;
  glViewport(0, 0, w, h);
}


int main(int argc, char *argv[])
{
	//pDefs.pxa=make2Dint(WIDTH,WIDTH);
//	pD.img=0;
//	color();
	//printf("made it\n");
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(WIDTH,HEIGHT);
  glutInitWindowPosition(50,50);
  glutCreateWindow("Image diffusion");
  glClearColor (0.0, 0.0, 0.0, 1.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();  
  glDisable(GL_LIGHTING);
  glutReshapeFunc(reshape);
  glutIdleFunc(display); 
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;   
}
