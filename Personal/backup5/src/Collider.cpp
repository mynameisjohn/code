#include "Collider.h"
#include <glm/glm.hpp>

#include <stdio.h>

//TODO
//figure out something wrt glm vectors versus a custom class...is it a big deal?

Collider::Collider(){
	w_x=0;
	w_y=0;
	w_z=0;
	w_X=400;
	w_Y=300;
	w_Z=300;
}

Collider::~Collider(){
	//NYI
}

void Collider::setBB(BoundBox bb){
	mBB = bb;
}

void Collider::addSub(iRect sub){
	mSubs.push_back(sub);
}

void Collider::setWalls(int x, int y, int z, int X, int Y, int Z){
	w_x=x;
	w_y=y;
	w_z=z;
	w_X=X;
	w_Y=Y;
	w_Z=Z;
}

void Collider::clearSub(){
	mSubs.clear();
}

void Collider::translate(int x, int y, int z){
	mBB.translate(x,y,z);
	
	std::vector<iRect>::iterator rectIt;
	for (rectIt=mSubs.begin(); rectIt!=mSubs.end(); rectIt++)
		rectIt->translate(x,y);
}

//This just moves the collider with respect to the walls
glm::vec3 Collider::move(glm::vec3 vel){
	glm::vec3 translate;

	//check wall collision, move accordingly in each dimension
	if (mBB.left() + vel.x < w_x)
		translate.x = (mBB.left() - w_x);
	else if (mBB.right() + vel.x > w_X)
		translate.x = (w_X - mBB.right());
	else
		translate.x += vel.x;

	if (mBB.top() + vel.y < w_y)
		translate.y = (mBB.top() - w_y);
	else if (mBB.bottom() + vel.y > w_Y)
		translate.y = (w_Y - mBB.bottom());
	else
		translate.y += vel.y;

	this->translate(translate.x, translate.y, translate.z);
/*
	if (mBB.near() + vel.z < w_z)
		translate.z = (mBB.near() - w_z);
	else if (mBB.far() + vel.z > w_Z)
		translate.z = (w_Z - mBB.far());
	else
		translate.z += vel.z;
*/
	
	return translate;
}

//This whole thing should be inlined or something
bool Collider::collidesX(Collider& other){
	return mBB.collidesX(other.mBB);
}
bool Collider::collidesY(Collider& other){
	return mBB.collidesY(other.mBB);
}

bool Collider::collidesZ(Collider& other){
	return mBB.collidesZ(other.mBB);
}

char Collider::collidesWith(Collider& other){
	bool colX, colY, colZ;
	colX = mBB.collidesX(other.mBB);
	colY = mBB.collidesY(other.mBB);
	colZ = mBB.collidesZ(other.mBB);
	
	return cBuf.handleCollision(colX, colY, colZ);
}

//Checks to see if a) bounding boxes collided and b) one of the sub-rects overlap
bool Collider::overlapsWith(Collider& other){
	if (collidesWith(other)){
		std::vector<iRect>::iterator rectIt1, rectIt2;
		for (rectIt1=mSubs.begin(); rectIt1!=mSubs.end(); rectIt1++){
			for (rectIt2=mSubs.begin(); rectIt2!=mSubs.end(); rectIt2++){
				if (rectIt1->overlapsWith(*rectIt2))
					return true;
			}
		}
	}
	return false;
}
