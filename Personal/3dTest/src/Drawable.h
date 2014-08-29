#ifndef DRAWABLE_H
#define DRAWABLE_H
#include <GL/gl.h>

#ifndef GLM_FORCE_RADIANS 
#define GLM_FORCE_RADIANS 
#endif

#include <glm/glm.hpp>
//#include "Entity.h"

using glm::mat4;
using glm::vec3;

class Drawable{
	public:
		Drawable();
		~Drawable();
		void identity();
		void translate(GLfloat x, GLfloat y, GLfloat z);
		void setPos(vec3 pos);
		void setMV(glm::mat4 newMatrix);
		void setVAO(GLuint VAO);
		void setTex(GLuint tex);
		void setColor(float r, float g, float b);
		void setColor(vec3 color);
		void leftMultMV(glm::mat4 left);
		void setNElements(int n);
		void uploadData(GLint MVHandle, GLint ColorHandle);
		void draw(GLint MVHandle, GLint ColorHandle);
		bool isVisible();
		int getNumElems();
		GLuint getVAO();
		GLuint getTex();
		GLfloat * getMVPtr();
		GLfloat * getColorPtr();
		glm::mat4 getMVMat();
	private:
		glm::mat4 MV;
		glm::vec4 mColor; //probably phase this out
		glm::vec3 mPos;
		GLuint mVAO, mTex;
		bool visible;
		int mElementCount;
};

#endif
