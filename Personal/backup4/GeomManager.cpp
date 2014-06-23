#include <GL/glew.h>
#include "GeomManager.h"

bool initSquare(Drawable * dr, int x, int y, int vHandle, int tHandle){
   const int nVert=4, dim=2, nIndices=4;
   const int vStride = 4*2*sizeof(GLint);
   const int tStride = 4*2*sizeof(GLfloat);
   const int iStride = 4*sizeof(GLuint);

   const GLint vertices[nVert][dim] = {
      {0, 0}, {40, 0},
      {0, 40}, {40, 40}
   };
   const GLfloat texCoords[nVert][dim] = {
      {0.f, 0.f}, {1.f, 0.f},
      {0.f, 1.f}, {1.f, 1.f}
   };
   const GLuint indices[4] = {0, 1, 2, 3};

   GLuint tmpVAO;
   glGenVertexArrays(1, &tmpVAO);
   glBindVertexArray(tmpVAO);

   GLuint buffers[3];
   glGenBuffers(3, buffers);

   //vertices
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
   glBufferData(GL_ARRAY_BUFFER, vStride, vertices, GL_STATIC_DRAW);
   glEnableVertexAttribArray(vHandle);
   glVertexAttribPointer(vHandle, dim, GL_INT, 0, 0, 0);

   //tex coords
   glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
   glBufferData(GL_ARRAY_BUFFER, tStride, texCoords, GL_STATIC_DRAW);
   glEnableVertexAttribArray(tHandle);
   glVertexAttribPointer(tHandle, dim, GL_FLOAT, 0, 0, 0);

   //indices
   glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, buffers[2] );
   glBufferData( GL_ELEMENT_ARRAY_BUFFER, iStride, indices, GL_STATIC_DRAW );

   glBindVertexArray(0);

   dr->leftMultMV(glm::translate(glm::vec3(x, y, 0)));
   iRect top;
   top.x=x; top.y=y;
   top.w=40; top.h=40;
   //shift(top, x, y);

   if (dr->hasEntity()){
      dr->getEntityPtr()->setTop(top);
      dr->setColor(0.1f, 0.3f, 0.6f);
   }
   else if (dr->hasCollider()){
      dr->getColPtr()->setTop(top);
      dr->setColor(0.4f, 0.6f, 0.2f);
   }

   dr->setVAO(tmpVAO);

   return true;
}

