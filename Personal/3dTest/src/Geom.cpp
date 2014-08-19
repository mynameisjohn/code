#ifndef GEOM_H
#define GEOM_H

#include "JShader.h"
#include "Drawable.h"

Drawable initQuad(glm::mat4 MV, JShader& shader){
   const int nVert=4, dim=3, nIndices=4;
   const int vStride = nVert*dim*sizeof(GLint);
   const int tStride = nVert*2*sizeof(GLfloat);
   const int iStride = nIndices*sizeof(GLuint);

	Drawable dr;

   const GLint vertices[nVert][dim] = {
		{0, 0, 0}, {1, 0, 0},
		{0, 1, 0}, {1, 1, 0}
	};

	//why 3?
   const GLfloat texCoords[nVert][3] = {
      {0.f, 0.f}, {1.f, 0.f},
      {0.f, 1.f}, {1.f, 1.f}
   };
   const GLuint indices[nIndices] = {0, 1, 2, 3};

   GLuint tmpVAO;
   glGenVertexArrays(1, &tmpVAO);
   glBindVertexArray(tmpVAO);

   GLuint buffers[3];
   glGenBuffers(3, buffers);

   //vertices
   glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
   glBufferData(GL_ARRAY_BUFFER, vStride, vertices, GL_STATIC_DRAW);
   glEnableVertexAttribArray(shader.getPosHandle());
   glVertexAttribPointer(shader.getPosHandle(), dim, GL_INT, 0, 0, 0);

   //tex coords
   glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
   glBufferData(GL_ARRAY_BUFFER, tStride, texCoords, GL_STATIC_DRAW);
   glEnableVertexAttribArray(shader.getTexCoordHandle());
   glVertexAttribPointer(shader.getTexCoordHandle(), dim, GL_FLOAT, 0, 0, 0);

   //indices
   glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, buffers[2] );
   glBufferData( GL_ELEMENT_ARRAY_BUFFER, iStride, indices, GL_STATIC_DRAW );

   glBindVertexArray(0);

	dr.setVAO(tmpVAO);
	dr.setMV(MV);

   return dr;
}

#endif
