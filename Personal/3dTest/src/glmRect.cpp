#include "glmRect.h"

std::ostream& operator<<(std::ostream& os, const glm::vec2& vec){
  std::cout << "<" << vec.x << ", " << vec.y << ">";
  return os;
}

glmRect::glmRect(){
	mPos=vec2();
	mDim=vec2(100.f, 100.f);
}

glmRect::glmRect(vec2 dim){
	mPos=vec2();
	mDim=glm::abs(dim);
}

glmRect::glmRect(vec2 pos, vec2 dim){
	mPos=pos;
	mDim=glm::abs(dim);
}

float glmRect::left(){
	return mPos.x;
}

float glmRect::right(){
	return mPos.x+mDim.x;
}

float glmRect::bottom(){
	return mPos.y;
}

float glmRect::top(){
	return mPos.y+mDim.y;
}

vec2 glmRect::getPos(){
	return mPos;
}

vec2 glmRect::getDim(){
	return mDim;
}

/*
iRect::iRect(){
	x=0; y=0;
	w=40; h=40;
}

iRect::iRect(int w, int h){
	x=0; y=0;
	this->w=w; this->h=h;
}

iRect::iRect(int x, int y, int w, int h){
	this->x=x; this->y=y;
	this->w=w; this->h=h;
}

void iRect::translate(int x, int y){
	this->x+=x;
	this->y+=y;
}
*/
