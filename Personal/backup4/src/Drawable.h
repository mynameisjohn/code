#ifndef DRAWABLE_H
#define DRAWABLE_H
//GLM Stuff
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <GL/gl.h>
#include "Entity.h"

//Anything that isn't VAO can be removed

class Drawable{
	public:
		Drawable();
		~Drawable();
		void setMV(glm::mat4 newMatrix);
		void setColor(float r, float g, float b);
		void setVAO(GLuint  VAO);
		void setVBO(GLint VBO);
		void setIBO(GLint IBO);
		void setTBO(GLint TBO);
		GLuint getVAO();
		GLint getVBO();
		GLint getIBO();
		GLint getTBO();
		void leftMultMV(glm::mat4 left);
		bool isVisible();
		void setEntity(Entity * e);
		bool hasEntity();
		void setCollider(Collider * c);
		void setTop(iRect rect);
		bool hasCollider();
		void getEntityMV();
		Entity * getEntityPtr();
		Collider * getColPtr();
		GLfloat * getMVPtr();
		GLfloat * getColorPtr();
	private:
		glm::mat4 MV;
		glm::vec4 mColor; //probably phase this out
		glm::vec4 mStepColor; //yup
		GLint mVBO, mIBO, mTBO;
		GLuint mVAO;
		bool visible;
		bool isEntity;
		Entity * myEntity;
		Collider * myCollider;
};

#endif
