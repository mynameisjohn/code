#include <GL/gl.h>
#include "Drawable.h"

Drawable::Drawable(){
	MV = glm::mat4();
	mColor = {1.f, 1.f, 1.f, 1.f};
	mStepColor = {0.8f, 0.4f, 0.3f, 1.f};
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

void Drawable::setVAO(GLuint VAO){
	mVAO = VAO;
}

void Drawable::setVBO(GLint VBO){
	mVBO = VBO;
}

void Drawable::setIBO(GLint IBO){
	mIBO = IBO;
}

void Drawable::setTBO(GLint TBO){
	mTBO = TBO;
}

GLuint Drawable::getVAO(){
	return mVAO;
}

GLint Drawable::getVBO(){
	return mVBO;
}

GLint Drawable::getIBO(){
	return mIBO;
}

GLint Drawable::getTBO(){
	return mTBO;
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
	//if (myEntity->isSteppedOn())
		//return glm::value_ptr(mStepColor);
	return glm::value_ptr(mColor);
}
