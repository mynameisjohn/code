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

int main(int argc, char ** argv){
   Mat src, dst, kernel;
   Point anchor;
   double delta;
   int ddepth, kernel_size,c, ind;
   char * window_name = "filter 2D Demo";

   src = imread(argv[1]);
   
   if (!src.data) return -1;

   namedWindow(window_name,CV_WINDOW_AUTOSIZE);

   anchor = Point(-1,-1);
   delta = 0;
   ddepth = -1;
   ind = 0;

   while (true){
      c=waitKey(500);
      if ((char)c==27) break;
      
      kernel_size = 3 + 2*(ind%5);     
      //kernel = Mat::ones( kernel_size, kernel_size, CV_32F )/ (float)(kernel_size*kernel_size);
      kernel = dogKernel(kernel_size); 
      /// Apply filter
      filter2D(src, dst, ddepth , kernel, anchor, delta, BORDER_DEFAULT );
      imshow( window_name, dst );
      ind++;
   }

   std::cout << kernel.channels() << std::endl;

   return 0;
}
