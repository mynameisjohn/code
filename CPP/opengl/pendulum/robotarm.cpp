// This program is from the OpenGL Programming Guide.  It shows a robot arm

// that you can rotate by pressing the arrow keys.

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define PEND_X 2.0
#define PEND_Y 0.25
#define PEND_Z 0.25

#define ORB_R 0.5
#define ORB_SL 10
#define ORB_ST 10
/*
#define DT 0.001
#define G 9.8
#define L 2.0
#define M 1.0
*/
float DT=0.0001, G=9.8, L=2.0,M=1.0;
float thD1=0.0;
float thD2=0.0;
float p1=0.0; //=M*L*L*(2*thD1+thD2*cos(degToRad(45.0)-degToRad(45.0)));
float p2=0.0; //M*L*L*(thD1*cos(degToRad(45.0)-degToRad(45.0)))+thD2;
float piO=(float)M_PI/((float)180.0);

float solveRD (float x0, float a, float b)
{
  return x0*exp(-a*DT)+b;
}

float eulerAdvance(float x0, float v, float dt)
{
  return x0 + dt * v;
}


float solveRK (float x0, float a, float b)
{
  float k1,k2,k3,k4,s;

  k1 = a*x0+b;
  k2 = a*eulerAdvance(x0,k1,DT/2)+b;
  k3 = a*eulerAdvance(x0,k2,DT/2)+b;
  k4 = a*eulerAdvance(x0,k3,DT)+b;
  s = (k1+2*k2+2*k3+k4);
  return eulerAdvance(x0,s,DT/6.0);
}

// The robot arm is specified by (1) the angle that the upper arm makes
// relative to the x-axis, called shoulderAngle, and (2) the angle that the
// lower arm makes relative to the upper arm, called elbowAngle.  These angles
// are adjusted in 5 degree increments by a keyboard callback.
static int shoulderAngle = 0, elbowAngle = 0;
static float camTh=0.0;
// Handles the keyboard event: the left and right arrows bend the elbow, the
// up and down keys bend the shoulder.
void special(int key, int, int) {
  switch (key) {
    case GLUT_KEY_LEFT: (camTh += 0.01); break;
    case GLUT_KEY_RIGHT: (camTh -= 0.01); break;
    //case GLUT_KEY_UP: (shoulderAngle += 5) %= 360; break;
    //case GLUT_KEY_DOWN: (shoulderAngle -= 5) %= 360; break;
    default: return;
  }
  glutPostRedisplay();
}

// wireBox(w, h, d) makes a wireframe box with width w, height h and
// depth d centered at the origin.  It uses the GLUT wire cube function.
// The calls to glPushMatrix and glPopMatrix are essential here; they enable
// this function to be called from just about anywhere and guarantee that
// the glScalef call does not pollute code that follows a call to myWireBox.
void wireBox(GLdouble width, GLdouble height, GLdouble depth) {
  glPushMatrix();
  glScalef(width, height, depth);
  glutWireCube(1.0);
  glPopMatrix();
}

// wireSphere(r,sl,st)
// Draws a sphere at the current origin
// with a radius r, sl slices around and
// st stacks top to bottom 
void wireSphere(GLdouble r, GLint sl, GLint st) {
  glPushMatrix();
  glutWireSphere(r,sl,st);
  glPopMatrix();
}
float th1 = 1.57, th2=0.0;

// Displays the arm in its current position and orientation.  The whole
// function is bracketed by glPushMatrix and glPopMatrix calls because every
// time we call it we are in an "environment" in which a gluLookAt is in
// effect.  (Note that in particular, replacing glPushMatrix with
// glLoadIdentity makes you lose the camera setting from gluLookAt).
void display() {
  //static float dTheta= 1.0;
  //static float camTh = 0.0;
  glRotatef((GLfloat)camTh,1.0,0.0,0.0);
  if (camTh > 30 || camTh < -30) camTh = 0;
  //printf("%lf\n",theta);
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
//glRotatef((GLfloat)camTh,1.0,0.0,0.0);
  //if (camTh > 30 || camTh < -30) camTh = 0;

  // Draw the upper arm, rotated shoulder degrees about the z-axis.  Note that
  // the thing about glutWireBox is that normally its origin is in the middle
  // of the box, but we want the "origin" of our box to be at the left end of
  // the box, so it needs to first be shifted 1 unit in the x direction, then
  // rotated.
  //glRotatef((GLfloat)(camTh+=0.1),0.0,1.0,0.0);
  glRotatef((GLfloat)th1*180.0/M_PI, 0.0, 0.0, 1.0);
  glTranslatef((PEND_X/2.0), 0.0, 0.0);
  wireBox(PEND_X,PEND_Y,PEND_Z);
  glTranslatef((PEND_X/2.0),0.0,0.0);
  wireSphere(ORB_R,ORB_SL,ORB_ST);
  glTranslatef(-(PEND_X/2.0),0.0,0.0);
  // Now we are ready to draw the lower arm.  Since the lower arm is attached
  // to the upper arm we put the code here so that all rotations we do are
  // relative to the rotation that we already made above to orient the upper
  // arm.  So, we want to rotate elbow degrees about the z-axis.  But, like
  // before, the anchor point for the rotation is at the end of the box, so
  // we translate <1,0,0> before rotating.  But after rotating we have to
  // position the lower arm at the end of the upper arm, so we have to
  // translate it <1,0,0> again.
  glTranslatef((PEND_X/2.0), 0.0, 0.0);
  glRotatef((GLfloat)th2*180.0/M_PI, 0.0, 0.0, 1.0);
  glTranslatef((PEND_X/2.0), 0.0, 0.0);
  wireBox(PEND_X,PEND_Y,PEND_Z);
  glTranslatef((PEND_X/2.0),0.0,0.0);
  wireSphere(ORB_R,ORB_SL,ORB_ST);
  glTranslatef(-(PEND_X/2.0),0.0,0.0);


  glPopMatrix();
  //glRotatef((GLfloat)(camTh+=0.00001),0.0,1.0,0.0);

  glFlush();
//update();
  //theta = (theta+DTHETA);
  //if (theta > 360) theta = 0;
}

// Handles the reshape event by setting the viewport so that it takes up the
// whole visible region, then sets the projection matrix to something reason-
// able that maintains proper aspect ratio.
void reshape(GLint w, GLint h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(65.0, GLfloat(w)/GLfloat(h), 1.0, 20.0);
}

double degToRad(float deg){
  double result = (double)(deg*M_PI/180.0);
  if (!(result == result)){
     printf("this fucked up at %lf\n",deg);
     exit(0);
  }
  return result;
}

// Perfroms application specific initialization: turn off smooth shading,
// sets the viewing transformation once and for all.  In this application we
// won't be moving the camera at all, so it makes sense to do this.
void init() {
  glShadeModel(GL_FLAT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glRotatef(-90.0,0.0,0.0,1.0);
  gluLookAt(1,2,8, 0,0,0, 0,1,0);

  p1=M*L*L*(2*thD1+thD2*cos(degToRad(45.0)-degToRad(45.0)));
  p2=M*L*L*(thD1*cos(degToRad(45.0)-degToRad(45.0)))+thD2;
}
/*
float degToRad(float deg){
  return deg*M_PI/180.0;
}

static float thD1=0.0;
static float thD2=0.0;
static float p1=0.0; //=M*L*L*(2*thD1+thD2*cos(degToRad(45.0)-degToRad(45.0)));
static float p2=0.0; //M*L*L*(thD1*cos(degToRad(45.0)-degToRad(45.0)))+thD2;
*/
void update(){
/*  static float thD1=0.0;
  static float thD2=0.0;
  static float p1=M*L*L*(2*thD1+thD2*cos(degToRad(45.0)-degToRad(45.0)));
  static float p2=M*L*L*(thD1*cos(degToRad(45.0)-degToRad(45.0)))+thD2;
*/
  int i;
  float save[8];
  
  if (!(th1 == th1) || !(th2==th2) || !((th1-th2)==(th1-th2))){
    printf("%lf\t%lf\t%lf\n",th1,th2,th1-th2);
    exit(0);
  }

  save[0]=th1;
  save[1]=th2;
  save[2]=thD1;
  save[3]=thD2;
  save[4]=p1;
  save[5]=p2;

  for (i=0;i<20;i++){
  float C = (float)cos(th1-th2);
  float S = (float)sin(th1-th2);

  save[6]=C;
  save[7]=S;

  //float thDD1, thDD2;
  //float C = cos(degToRad(th1-th2));
  //float S = sin(degToRad(th1-th2));
//  float MLL = M*L*L;
  thD1=(p1-p2*C)/(M*L*L*(2-C*C));
  thD2=(-p1*C+2*p2)/(M*L*L*(2-C*C));
  p1  = solveRK(p1,0.0,M*L*L*(-thD1*thD2*S-2*G*sin(th1)));
  p2  = solveRK(p2,0.0,M*L*L*(thD1*thD2*S-G*sin(th2)));
  th1 = solveRK(th1,0.0,thD1);
  th2 = solveRK(th2,0.0,thD2);
/*
thDD1 = sin(degToRad(theta))*(G/L); //solveRK(thDD,0.0,sin(degToRad(theta))*(G/L));
  //thDD = (G/L)*sin(degToRad(theta));
  thD1   = solveRK(thD1,0.0,thDD1);
  theta = solveRK(theta,0.0,thD1);
*/
  //printf("%lf\t%lf\t%lf\n",p1,thD1,th1);

  if (th1 > 360) th1 = 0;
  if (th2 > 360) th2 = 0;

  //printf("%lf\t%lf\t%lf\n",th1,th2,th1-th2);
  if (!(C==C) || !(S==S)){
	printf("theta 1:%lf\n theta 2:%lf\n dTheta1:%lf\n dTheta2:%lf\n p1:%lf\n p2:%lf\n C:%lf\n D:%lf\n",save[0],save[1],save[2],save[3],save[4],save[5],save[6],save[7]);
	exit(0);
  }
}
  glutPostRedisplay();
}

// Initializes GLUT, the display mode, and main window; registers callbacks;
// does application initialization; enters the main event loop.
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(80, 80);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Robot Arm");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutSpecialFunc(special);
  glutIdleFunc(update);
  init();
  glutMainLoop();
}
