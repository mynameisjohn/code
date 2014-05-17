#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
using namespace std;

template <class T>
class mypair{
   T a, b;
   public:
      mypair (T first, T second)
	 {a=first; b=second;}
      T getMax ();
};

template <class T>
T mypair<T>::getMax ()
{
   T retval;
   retval = a>b? a : b;
   return retval;
}

class Quaternion{
   float s, x, y, z;
   public:
      static int counter;
      void set_values(float s, float x, float y, float z);
      void set_rotation(float theta, float x, float y, float z);
      float * getMatrix();
      void print();
      Quaternion (float, float, float, float, bool);
      Quaternion();
      ~Quaternion(){counter--;};
      const float& getS() const {return s;};
      float& getS() {return s;};
   private:
      void normalize();
};

class mypair<Quaternion>{
   Quaternion a,b;
   public:
      mypair(Quaternion A, Quaternion B){a=A;b=B;};
      makeConj(){
         b.x=-a.x;
         b.y=-a.y;
         b.z=-a.z;
      }
}


int Quaternion::counter=0;

void Quaternion::set_values(float S, float X, float Y, float Z){
   s=S;
   x=X;
   y=Y;
   z=Z;
   normalize();
   return;
}

void Quaternion::set_rotation(float theta, float X, float Y, float Z){
   s=cos(theta/2.);
   float im=sin(theta/2.);
   x=im*X;
   y=im*Y;
   z=im*Z;
   normalize();
   return;
}

void Quaternion::normalize(){
   float m = sqrt(x*x+y*y+z*z);
   x/=m;
   y/=m;
   z/=m;
   return;
}


Quaternion::Quaternion(float A, float B, float C, float D, bool fromRotation){
   if (fromRotation) set_rotation(A,B,C,D);
   else set_values(A,B,C,D);
   counter++;
}

Quaternion::Quaternion(){
   s=1.;
   x=1.;
   y=1.;
   z=1.;
   normalize();
   counter++;
}

void Quaternion::print(){
   printf("<%lf,%lf,%lf,%lf>\n",s,x,y,z);
   return;
}

float * Quaternion::getMatrix(){
   float * R = (float *)malloc(sizeof(float)*16);
   
   R[0]=1-2*(y*y+z*z); R[1]=2*(x*y-z*s); R[2]=2*(x*z+y*s); R[3]=0;
   R[4]=2*(x*y+z*s); R[5]=1-2*(x*x+z*z); R[6]=2*(y*z-x*s); R[7]=0;
   R[8]=2*(x*z-y*s); R[9]=2*(s*z+x*s); R[10]=1-2*(x*x+y*y); R[11]=0;
   R[12]=0; R[13]=0; R[14]=0; R[15]=1;

   return R;
}

int main(){
   Quaternion * q = new Quaternion(30.*M_PI/180,1.,0.,0.,true);
   q->print();
   float * R = q->getMatrix();
   for (int i=0;i<16;i++) printf("%lf\n",R[i]);
   free(R);
   delete q;

   Quaternion qs [10];

   const Quaternion c(10.*M_PI/180,1.,0.,0.,true);
   cout << c.getS() << endl;

   cout << qs[0].getS() << endl;
   cout << Quaternion::counter << endl;

   mypair<int> myobject(100,75);
   cout << myobject.getMax() << endl;

   Quaternion x,y;

   mypair<Quaternion> quatPair(x,y);

   return 0;
}
