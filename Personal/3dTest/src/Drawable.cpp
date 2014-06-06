#include <GL/gl.h>
#include "Drawable.h"

Drawable::Drawable(){
	MV = glm::mat4();
	mColor = {1.f, 1.f, 1.f, 1.f};
	mVBO = -1;
	mIBO = -1;
	visible = true;
	isEntity = false;
	myEntity = NULL;
	myCollider = NULL;
}

Drawable::~Drawable(){
	mVBO = -1;
	mIBO = -1;
}

void Drawable::setMV(glm::mat4 newMatrix){
	MV = newMatrix;
}

void Drawable::setColor(float r, float g, float b){
	mColor.x=r;
	mColor.y=g;
	mColor.z=b;
	mColor.w=1.f;
}

void Drawable::setVBO(GLint VBO){
	mVBO = VBO;
}

void Drawable::setIBO(GLint IBO){
	mIBO = IBO;
}

GLint Drawable::getVBO(){
	return mVBO;
}

GLint Drawable::getIBO(){
	return mIBO;
}

void Drawable::leftMultMV(glm::mat4 left){
	MV = left * MV;
}

bool Drawable::isVisible(){
	return visible;
}

void Drawable::setEntity(Entity * e){
	myEntity = e;
}

bool Drawable::hasEntity(){
	return myEntity != NULL;
}

void Drawable::setCollider(Collider * c){
	myCollider = c;
}

bool Drawable::hasCollider(){
	return myCollider != NULL;
}

void Drawable::getEntityMV(){
	if (myEntity != NULL)
		leftMultMV(glm::translate(myEntity->getTranslate()));
}

Entity * Drawable::getEntityPtr(){
	return myEntity;
}

Collider * Drawable::getColPtr(){
	return myCollider;
}

GLfloat * Drawable::getMVPtr(){
	return glm::value_ptr(MV);
}

GLfloat * Drawable::getColorPtr(){
	return glm::value_ptr(mColor);
}
