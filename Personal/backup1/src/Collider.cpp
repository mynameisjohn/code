#include "Collider.h"

Collider::Collider(){
	mTop.x=0;
	mTop.y=0;
	mTop.w=10;
	mTop.h=10;
	wall_x=0;
	wall_y=0;
	wall_X=400;
	wall_Y=300;
}

Collider::~Collider(){
	mSub.clear();
}

void Collider::setTop(iRect top){
	mTop = top;
}

void Collider::addSub(iRect sub){
	mSub.push_back(sub);
}

void Collider::setWalls(int x, int y, int X, int Y){
	wall_x=x;
	wall_y=y;
	wall_X=X;
	wall_Y=Y;
}

glm::vec3 Collider::move(int velX, int velY){
	glm::vec3 translate = glm::vec3();
	int oldX = mTop.x;
	int oldY = mTop.y;

	if (mTop.x + velX < wall_x)
		mTop.x = wall_x;
	else if (mTop.x + mTop.w + velX > wall_X)
		mTop.x = wall_X - mTop.w;
	else
		mTop.x += velX;

	if (mTop.y + velY < wall_y)
		mTop.y = wall_y;
	else if (mTop.y + mTop.h + velY > wall_Y)
		mTop.y = wall_Y - mTop.h;
	else
		mTop.y += velY;

	translate.x = mTop.x - oldX;
	translate.y = mTop.y - oldY;

	return translate;
}

void Collider::clearSub(){
	mSub.clear();
}

bool Collider::collidesWith(Collider * other){
	//NYI
}
