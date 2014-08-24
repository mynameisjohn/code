#include <GL/gl.h>

#include "Textures.h"

int * outline(int DIM, int th){
	int * PXA = new int[DIM*DIM];
	int white = 0xFFFFFFFF;
	int black = 0xFF000000;

   for (int y=0; y<DIM; y++){
      for (int x=0; x<DIM; x++){
         if (x<th || x>DIM-th || y<th || y>DIM-th)
            PXA[y*DIM+x] = black;
         else
            PXA[y*DIM+x] = white;
      }
   }
	
	return PXA;
}

int * invertedOutline(int DIM, int th){
	int * PXA = new int[DIM*DIM];
	int white = 0xFFFFFFFF;
	int black = 0xFF000000;

   for (int y=0; y<DIM; y++){
      for (int x=0; x<DIM; x++){
         if (x<th || x>DIM-th || y<th || y>DIM-th)
            PXA[y*DIM+x] = white;
         else
            PXA[y*DIM+x] = black;
      }
   }
	
	return PXA;
}

unsigned int outlineTexture(){
	GLuint tex; //Device texture handle
   int DIM=100; //Texture dimension
	int th=8; //Outline thickness
   int * PXA; //Host texture storage(MUST BE FREED)

   //Create the outline texture on host
	PXA = outline(DIM, th);

   //Generate the device texture and bind it
   glGenTextures(1, &tex);
   glBindTexture(GL_TEXTURE_2D, tex);

   //Upload host texture to device
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, DIM, DIM, 0, GL_RGBA, GL_UNSIGNED_BYTE, PXA);

   // Set filtering
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

   //Delete the host texture, return handle to device texture
   delete PXA;
   return (unsigned int)tex;
}

unsigned int invertedOutlineTexture(){
	GLuint tex; //Device texture handle
   int DIM=100; //Texture dimension
	int th=8; //Outline thickness
   int * PXA; //Host texture storage(MUST BE FREED)

   //Create the outline texture on host
	PXA = invertedOutline(DIM, th);

   //Generate the device texture and bind it
   glGenTextures(1, &tex);
   glBindTexture(GL_TEXTURE_2D, tex);

   //Upload host texture to device
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, DIM, DIM, 0, GL_RGBA, GL_UNSIGNED_BYTE, PXA);

   // Set filtering
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

   //Delete the host texture, return handle to device texture
   delete PXA;
   return (unsigned int)tex;
}
