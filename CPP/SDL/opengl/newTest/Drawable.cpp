#include "Drawable.h"

Drawable::Drawable(){
	MV = glm::mat4();
	color = glm::vec4(1.f,1.f,1.f,1.f);
	mVBO = -1;
	mIBO = -1;
	//rect = {1.f,1.f,1.f,1.f};
}

Drawable::~Drawable(){
	mVBO = -1;
	mIBO = -1;
}

void Drawable::initGeom(){
/*	//VBO data
   GLfloat vertexData[] =
   {
      -50.f, -50.f,
       50.f, -50.f,
       50.f,  50.f,
      -50.f,  50.f
   };

   //IBO data
   GLuint indexData[] = { 0, 1, 2, 3 };

	//Create VBO
   glGenBuffers( 1, &mVBO );
   glBindBuffer( GL_ARRAY_BUFFER, mVBO );
   glBufferData( GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW );
*/
}

void Drawable::setMV(glm::mat4 newMV){
	MV = newMV;
}

void Drawable::setColor(glm::vec4 newColor){
	color = newColor;
}

void Drawable::setColor(glm::vec3 newColor){
	color = glm::vec4(newColor,1.f);
}

void Drawable::setColor(float r, float g, float b, float a){
	color = glm::vec4(r, g, b, a);
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

GLfloat * Drawable::getMVPtr(){
	return glm::value_ptr(MV);
}

GLfloat * Drawable::getColorPtr(){
	return glm::value_ptr(color);
}

void Drawable::leftMultMV(glm::mat4 left){
	MV = left * MV;
}
