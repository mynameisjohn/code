#include "Drawable.h"

Drawable::Drawable(){
	MV = glm::mat4();
	color = glm::vec4(1.f,1.f,1.f,1.f);
	mVBO = -1;
	mIBO = -1;
	speed = 10.f;
	visible = true;
}

Drawable::~Drawable(){
	mVBO = -1;
	mIBO = -1;
}

void Drawable::update(){

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

void Drawable::setTop(SDL_Rect top){
	mTopCol=top;
}

void Drawable::addSub(SDL_Rect sub){
	mSubCols.push_back(sub);
}
/*
void Drawable::handleEvent(SDL_Event& e){
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
		switch(e.key.keysym.sym){
			case SDLK_UP: mVelY -= speed; break;
         case SDLK_DOWN: mVelY += speed; break;
         case SDLK_LEFT: mVelX -= speed; break;
         case SDLK_RIGHT: mVelX += speed; break;
		}
   }
	else if ( e.type == SDL_KEYUP && e.key.repeat == 0 ){
      switch(e.key.keysym.sym){
         case SDLK_UP: mVelY += speed; break;
         case SDLK_DOWN: mVelY -= speed; break;
         case SDLK_LEFT: mVelX += speed; break;
         case SDLK_RIGHT: mVelX -= speed; break;
      }
   }
}
*/
void Drawable::move(){
	mTopCol.x += mVelX; mTopCol.y += mVelY;
	std::vector<SDL_Rect>::iterator rectIter;
	for (rectIter=mSubCols.begin(); rectIter != mSubCols.end(); rectIter++){
		rectIter->x += mVelX; rectIter->y += mVelY;
	}
	leftMultMV(glm::translate(glm::vec3(mVelX, mVelY, 0.f)));
}

bool Drawable::drawMe(){
	return visible;
}

SDL_Rect * Drawable::getTopColPtr(){
	return &mTopCol;
}
