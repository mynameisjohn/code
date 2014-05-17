#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

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
      kernel = Mat::ones(kernel_size, kernel_size,CV_32F);
      kernel /= (float)(kernel_size*kernel_size);
      
      /// Apply filter
      filter2D(src, dst, ddepth , kernel, anchor, delta, BORDER_DEFAULT );
      imshow( window_name, dst );
      ind++;
   }

   return 0;
}
