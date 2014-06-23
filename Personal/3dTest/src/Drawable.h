#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <GL/gl.h>
#include "Entity.h"

class Drawable{
	public:
		Drawable();
		~Drawable();
		void setMV(glm::mat4 newMatrix);
		void identity();
		void setColor(float r, float g, float b);
		void setVAO(GLuint  VAO);
		void translate(GLfloat x, GLfloat y, GLfloat z);
		void leftMultMV(glm::mat4 left);
		void setEntity(Entity * e);
		void updateMV();
		bool isVisible();
		GLuint getVAO();
		GLfloat * getMVPtr();
		GLfloat * getColorPtr();
	private:
		glm::mat4 MV;
		glm::vec4 mColor; //probably phase this out
		glm::vec3 mPos;
		GLuint mVAO;
		bool visible;
		Entity * myEntity;
};

#endif
