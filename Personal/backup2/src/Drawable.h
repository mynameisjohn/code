#ifndef DRAWABLE_H
#define DRAWABLE_H
//GLM Stuff
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <GL/gl.h>
#include "Entity.h"

class Drawable{
	public:
		Drawable();
		~Drawable();
		void setMV(glm::mat4 newMatrix);
		void setColor(float r, float g, float b);
		void setVBO(GLint VBO);
		void setIBO(GLint IBO);
		GLint getVBO();
		GLint getIBO();
		void leftMultMV(glm::mat4 left);
		bool isVisible();
		void setEntity(Entity * e);
		bool hasEntity();
		void getEntityMV();
		Entity * getEntityPtr();
		GLfloat * getMVPtr();
		GLfloat * getColorPtr();
	private:
		glm::mat4 MV;
		glm::vec4 mColor; //probably phase this out
		GLint mVBO, mIBO;
		bool visible;
		bool isEntity;
		Entity * myEntity;
};

#endif
