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

void Collider::moveTo(int x, int y){
	int tX = (x>0) ? x-mTop.x : 0;
	int tY = (y>0) ? y-mTop.y : 0;
	mTop.x+=tX;
	mTop.y+=tY;
	std::vector<iRect>::iterator iRiter;
	for (iRiter=mSub.begin();iRiter!=mSub.end();iRiter++){
		iRiter->x+=tX;
		iRiter->y+=tY;
	}
}
/*
char Collider::move(int velX, int velY, Collider * col, circBuf cBuf){
	bool colX = overlaps_X(col);
	bool colY = overlaps_Y(col);

	cBuf.update(colX, colY);
	
	return cBuf.last();
}
*/
void Collider::move(int velX, int velY, int& oldX, int& oldY){
	//glm::vec3 translate = glm::vec3();
	oldX = mTop.x;
	oldY = mTop.y;

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
/*
	translate.x = mTop.x - oldX;
	translate.y = mTop.y - oldY;

	return translate;
*/
}

glm::vec3 Collider::diff(int oldX, int oldY){
	glm::vec3 translate = {mTop.x-oldX, mTop.y-oldY, 0};
	return translate;
}

void Collider::clearSub(){
	mSub.clear();
}
/*
bool Collider::overlaps_X(Collider * other){
	mBB.overlaps_X(other->boundBox());
}

bool Collider::overlaps_Y(Collider * other){
	mBB.overlaps_Y(other->boundBox());
}
*/
bool Collider::overlaps_X(Collider& other){
	return !(right(mTop) <= left(other.mTop) || left(mTop) >= right(other.mTop));
}

bool Collider::overlaps_Y(Collider& other){
	return !(bottom(mTop) <= top(other.mTop) || top(mTop) >= bottom(other.mTop));
}

bool Collider::collidesWith(Collider& other){
	return (overlaps_X(other) && overlaps_Y(other));
}

int Collider::getTopTop(){
	return top(mTop);
}

int Collider::getTopBottom(){
	return bottom(mTop);
}

int Collider::getTopRight(){
	return right(mTop);
}

int Collider::getTopLeft(){
	return left(mTop);
}

int Collider::getTop_h(){
	return mTop.h;
}

int Collider::getTop_w(){
	return mTop.w;
}
