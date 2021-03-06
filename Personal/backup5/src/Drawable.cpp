#include "Drawable.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <stdio.h>

Drawable::Drawable(){
	MV = glm::mat4();
	mColor = {1.f, 1.f, 1.f, 1.f};
	mPos = glm::vec3();
	visible = true;
	myEntity = NULL;
}

Drawable::~Drawable(){
	mVAO = 0;
	myEntity = NULL;
}

void Drawable::setMV(glm::mat4 newMatrix){
	MV = newMatrix;
}

void Drawable::identity(){
	MV = glm::mat4();
}

void Drawable::setColor(float r, float g, float b){
	mColor.x=r;
	mColor.y=g;
	mColor.z=b;
	mColor.w=1.f;
}

void Drawable::setVAO(GLuint VAO){
	mVAO = VAO;
}

void Drawable::leftMultMV(glm::mat4 left){
	MV = left * MV;
}

void Drawable::setEntity(Entity * e){
	myEntity = e;
}

void Drawable::updateMV(){
	printf("Drawable thinks it's %ld\n", (long)(myEntity));
	glm::vec3 translate = myEntity->getPos() - mPos;
	leftMultMV(glm::translate(translate));
	mPos += translate;
}

bool Drawable::isVisible(){
	return visible;
}

GLuint Drawable::getVAO(){
	return mVAO;
}

GLfloat * Drawable::getMVPtr(){
	return glm::value_ptr(MV);
}

GLfloat * Drawable::getColorPtr(){
	return glm::value_ptr(mColor);
}
