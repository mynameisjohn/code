#include "Collider.h"
#include <glm/glm.hpp>

#include <stdio.h>

Collider::Collider(){
	w_x=0;
	w_y=0;
	w_z=0;
	w_X=400;
	w_Y=300;
	w_Z=300;
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

//I don't like these casts...I should bite the bullet and create an iVec class
glm::vec3 Collider::move(glm::vec3 vel){
	glm::vec3 translate; //(mBB.left(), mBB.bottom(),0.f); // mBB.top());

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

	this->translate((int)translate.x, (int)translate.y, (int)translate.z);
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

bool Collider::collidesX(Collider& other){
	return mBB.collidesX(other.mBB);
}
bool Collider::collidesY(Collider& other){
	return mBB.collidesY(other.mBB);
}

bool Collider::collidesZ(Collider& other){
	return mBB.collidesZ(other.mBB);
}

bool Collider::collidesWith(Collider& other){
	return mBB.collidesX(other.mBB) && mBB.collidesY(other.mBB) && mBB.collidesZ(other.mBB);
}

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
