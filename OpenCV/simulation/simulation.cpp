#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace cv;

Mat dogKernel(int size){
   Mat kernel(size,size,CV_32F);
   int i,j;
   for (i=-size/2;i<size/2+1;i++){
      int idx_Y=i+size/2;
      float * p = kernel.ptr<float>(idx_Y);
      for (j=-size/2;j<size/2+1;j++){
         int idx_X=j+size/2;
         float C=6.6,E=0.5,mu=1.,nu=4.;
         mu=-log(2.)/(mu*mu);
         nu=-log(2.)/(nu*nu);
         float r = (float)(j*j+i*i);
         p[idx_X]=C*exp((j*j+i*i)*mu)-E*exp((j*j+i*i)*nu);
      }
   }
   //if (size==13) std::cout << kernel << std::endl;
   return kernel;
}

Mat dogKernel2(int size){
   Mat kernel(size,size,CV_32F);
   int i,j;
   for (i=-size/2;i<size/2+1;i++){
      int idx_Y=i+size/2;
      float * p = kernel.ptr<float>(idx_Y);
      for (j=-size/2;j<size/2+1;j++){
         int idx_X=j+size/2;
         float C=6.6,E=0.0,mu=1.,nu=4.;
         mu=-log(2.)/(mu*mu);
         nu=-log(2.)/(nu*nu);
         float r = (float)(j*j+i*i);
         p[idx_X]=C*exp((j*j+i*i)*mu)-E*exp((j*j+i*i)*nu);
      }
   }
   //if (size==13) std::cout << kernel << std::endl;
   return kernel;
}

int main(int argc, char ** argv){
   Mat src, dst, kernel, poo, butt, X, xDot;
   Point anchor;
   double delta;
   int ddepth, kernel_size,c, ind;
   char * window_name = "filter 2D Demo";

   src = imread(argv[1],0);
   src.convertTo(src,CV_32F); 
   if (!src.data) return -1;

   namedWindow(window_name,CV_WINDOW_AUTOSIZE);

   anchor = Point(-1,-1);
   delta = 0;
   ddepth = -1;
   ind = 0;
   kernel_size=13;
   kernel = dogKernel(kernel_size);
   butt = dogKernel2(kernel_size);
   X = Mat::zeros(src.rows,src.cols,CV_32F);
   xDot = Mat::zeros(src.rows,src.cols,CV_32F);//src.clone();

   float t=0.,DT=0.0005,tMax=0.1;
   float A=1.5;

   filter2D(src,dst,ddepth,kernel,anchor,delta,BORDER_DEFAULT);
   filter2D(src,poo,ddepth,butt,anchor,delta,BORDER_DEFAULT);

   imshow(window_name,X);

   while (t<tMax){
      xDot=-A*X+poo-X.mul(dst);
      X=X+DT*xDot;
      t+=DT;
      imshow(window_name,X);
   }

   //imshow(window_name,X-dst);
   
   waitKey(0);

   return 0;
}
