/* Program which simulates the motion of a double pendulum
   by solving numerically the Lagrange equations.
   The one-step or Euler algorithm is not the best numerical 
   method to simulate the evolution of the system, but it is 
   used here because of its simplicity.

                                            Claudio Rebbi
                                            Boston University
                                            August 2011        */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define LENGTH 1.2
#define HEIGHT 1.2

float th1,th2,v1,v2,p1,p2;
float l=0.5, m=1, g=10; 
float t, dt=0.0005, tmax=10;
float K,V,E;
  
get_input(void)
{
  printf("Enter the initial values of theta1 and theta2 (in radians) or any character\n");
  printf("to quit:  ");
  if(!scanf("%f%f",&th1,&th2)) exit(0);
  printf("Enter the initial values of dtheta1/dt and dtheta2/dt:  ");
  scanf("%f%f",&v1,&v2);
  p1=m*l*l*(2*v1+v2*cos(th1-th2));
  p2=m*l*l*(v1*cos(th1-th2)+v2);
  K=m*l*l*(2*v1*v1+2*v1*v2*cos(th1-th2)+v2*v2);
  V=-m*g*l*(2*cos(th1)+cos(th2));
  E=K+V;
  printf("Initial energy:  %f\n",E);
  t=0;
}

void display(void)
{
  float x0,y0,x1,y1,x2,y2;
  float r,x,y;
  int i;

  glClear(GL_COLOR_BUFFER_BIT);

  x0=0;
  y0=0;
  x1=l*sin(th1);
  y1=-l*cos(th1);
  x2=x1+l*sin(th2);
  y2=y1-l*cos(th2);

  glDisable(GL_LIGHTING);

  glColor3f(0.,1.,0.);    
  glBegin(GL_LINE_STRIP);
  glVertex2f(x0,y0);    
  glVertex2f(x1,y1);    
  glEnd();
  glBegin(GL_LINE_STRIP);
  glVertex2f(x1,y1);    
  glVertex2f(x2,y2);    
  glEnd();

  glColor3f(1.,0.,0.);    
  glBegin(GL_LINE_STRIP);
  r=0.02;
  for(i=0;i<=20;i++){
    x=x1+r*cos((M_PI*i)/10);
    y=y1+r*sin((M_PI*i)/10);
    glVertex2f(x,y);    
  }
  r=0.01;
  for(i=0;i<=20;i++){
    x=x1+r*cos((M_PI*i)/10);
    y=y1+r*sin((M_PI*i)/10);
    glVertex2f(x,y);    
  }
  glEnd();
  glBegin(GL_LINE_STRIP);
  r=0.02;
  for(i=0;i<=20;i++){
    x=x2+r*cos((M_PI*i)/10);
    y=y2+r*sin((M_PI*i)/10);
    glVertex2f(x,y);    
  }
  r=0.01;
  for(i=0;i<=20;i++){
    x=x2+r*cos((M_PI*i)/10);
    y=y2+r*sin((M_PI*i)/10);
    glVertex2f(x,y);    
  }
  glEnd();
  

  glFlush(); 
  glutSwapBuffers();

  v1=(p1-p2*cos(th1-th2))/(m*l*l*(2-cos(th1-th2)*cos(th1-th2)));
  v2=(-p1*cos(th1-th2)+2*p2)/(m*l*l*(2-cos(th1-th2)*cos(th1-th2)));
  p1=p1+m*l*l*(-v1*v2*sin(th1-th2)-2*g*sin(th1))*dt;
  p2=p2+m*l*l*(v1*v2*sin(th1-th2)-g*sin(th2))*dt;
  th1=th1+v1*dt;
  th2=th2+v2*dt;
  t=t+dt;

  if(t>tmax) {
    K=m*l*l*(2*v1*v1+2*v1*v2*cos(th1-th2)+v2*v2);
    V=-m*g*l*(2*cos(th1)+cos(th2));
    E=K+V;
    printf("Final energy:    %f\n\n",E);
    get_input();
  }
}

void reshape(int w, int h)
{
  glViewport(0, 0, w, h);
}

main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(800,800);
  glutInitWindowPosition(50,50);
  glutCreateWindow("Double pendulum");
  glClearColor (0.0, 0.0, 0.0, 1.0);
  glDisable(GL_LIGHTING);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-LENGTH, LENGTH, -HEIGHT, HEIGHT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();  
  glEnable(GL_LINE_SMOOTH);
  glLineWidth(2.0);
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutIdleFunc(display); 
  get_input();
  glutMainLoop();
  return 0;   
}

