#include <GL/glew.h>
#include "Drawable.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <stdio.h>

Drawable::Drawable(){
	MV = mat4();
	mColor = {1.f, 1.f, 1.f, 1.f};
	mPos = glm::vec3();
	visible = true;
	mElementCount=4;
}

Drawable::~Drawable(){
	mVAO = 0;
}

void Drawable::setPos(vec3 pos){
	mPos = pos;
}

void Drawable::setMV(mat4 newMatrix){
	MV = newMatrix;
}

void Drawable::identity(){
	MV = mat4();
}

void Drawable::setColor(float r, float g, float b){
	mColor.x=r;
	mColor.y=g;
	mColor.z=b;
	mColor.w=1.f;
}

void Drawable::setColor(vec3 color){
	mColor = glm::vec4(color, 1.f);
}

void Drawable::setVAO(GLuint VAO){
	mVAO = VAO;
}

void Drawable::setTex(GLuint tex){
	mTex = tex;
}

void Drawable::leftMultMV(mat4 left){
	MV = left * MV;
}

void Drawable::setNElements(int n){
	mElementCount = n;
}

void Drawable::draw(GLint MVHandle, GLint ColorHandle){
	uploadData(MVHandle, ColorHandle); //send MV matrix and color to GPU
	glBindTexture(GL_TEXTURE_2D, mTex); //Make my texture active
	glBindVertexArray(mVAO); //Bind my VAO
	glDrawElements(GL_TRIANGLE_STRIP, mElementCount, GL_UNSIGNED_INT, NULL);
}

void Drawable::uploadData(GLint MVHandle, GLint ColorHandle){
	glUniformMatrix4fv(MVHandle, 1, GL_FALSE, glm::value_ptr(MV));
	glUniform4fv(ColorHandle, 1, glm::value_ptr(mColor));
}

bool Drawable::isVisible(){
	return visible;
}

int Drawable::getNumElems(){
	return mElementCount;
}

GLuint Drawable::getVAO(){
	return mVAO;
}

GLuint Drawable::getTex(){
	return mTex;
}

GLfloat * Drawable::getMVPtr(){
	return glm::value_ptr(MV);
}

GLfloat * Drawable::getColorPtr(){
	return glm::value_ptr(mColor);
}


mat4 Drawable::getMVMat(){
	return MV;
}
