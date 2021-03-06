#include "Collider.h"
#include <stdio.h>

//Collider shouldn't own this info...
Collider::Collider(){
	W_min=vec3(); 
	W_max=vec3(1000, 1000, -1000);
	cBufMap.clear();
}

Collider::Collider(vec3 w_min, vec3 w_max, BoundBox bb){
	W_min=w_min;
	W_max=w_max;
	mBB = bb;
	cBufMap.clear();
}

Collider::~Collider(){
	cBufMap.clear();
}

void Collider::ground(){
	grounded = true;
}

void Collider::setBB(BoundBox bb){
	mBB = bb;
}

void Collider::addSub(BoundRect sub){
	mSubs.push_back(sub);
}

void Collider::setWalls(vec3 min, vec3 max){
	W_min=min;
	W_max=max;
}

void Collider::clearSub(){
	mSubs.clear();
}

void Collider::translate(vec3 trans){
	mBB.translate(trans);
	
	std::vector<BoundRect>::iterator rectIt;
	for (rectIt=mSubs.begin(); rectIt!=mSubs.end(); rectIt++){
		rectIt->translate(vec2(trans));
//		std::cout << rectIt->getPos() << std::endl;
	}
}

bool Collider::isGrounded(){
	return grounded;
}

//This whole thing should be inlined or something
bool Collider::collidesX(Collider * other){
	return mBB.collidesX(other->mBB);
}
bool Collider::collidesY(Collider * other){
	return mBB.collidesY(other->mBB);
}

bool Collider::collidesZ(Collider * other){
	return mBB.collidesZ(other->mBB);
}

char Collider::collidesWith(Collider * other){
	bool colX, colY, colZ;
	colX = collidesX(other);
	colY = collidesY(other);
	colZ = collidesZ(other);
	
	return cBufMap[other].handleCollision(colX, colY, colZ);
}

//Checks to see if a) bounding boxes collided and b) one of the sub-rects overlap
bool Collider::overlapsWith(Collider * other){
// with this uncommented we don't interact with the map; I think it's ok for now
// if (collidesX(other) && collidesY(other) && collidesZ(other)){
	if (collidesWith(other)){
		std::vector<BoundRect>::iterator rectIt1, rectIt2;
		for (rectIt1=mSubs.begin(); rectIt1!=mSubs.end(); rectIt1++){
			for (rectIt2=mSubs.begin(); rectIt2!=mSubs.end(); rectIt2++){
				if (rectIt1->collidesWith(*rectIt2))
					return true;
			}
		}
	}
	return false;
}

float Collider::toLeft(Collider * c){
	return c->mBB.left()-mBB.right(); 
}

float Collider::toRight(Collider * c){
	return c->mBB.right()-mBB.left(); 
}

float Collider::toBottom(Collider * c){
	return c->mBB.bottom()-mBB.top(); 
}

float Collider::toTop(Collider * c){
	return c->mBB.top()-mBB.bottom(); 
}

float Collider::toNear(Collider * c){
	return c->mBB.near() - mBB.far();
}

float Collider::toFar(Collider * c){
	return c->mBB.far()-mBB.near(); 
}

vec3 Collider::center(){
	return mBB.center();
}

vec3 Collider::getPos(){
	return mBB.getPos();
}

//This just moves the collider with respect to the walls - will be phased out soon
vec3 Collider::move(vec3 vel){
	grounded=false;
	vec3 T;
	
	//check wall collision, move accordingly in each dimension
	if (mBB.left() + vel.x < W_min.x)
		T.x = W_min.x-mBB.left();//These somehow got reversed...be careful	
	else if (mBB.right() + vel.x > W_max.x)
		T.x = W_max.x - mBB.right();
	else
		T.x += vel.x;

	if (mBB.bottom() + vel.y < W_min.y){
		T.y = W_min.y-mBB.bottom();
		ground();
	}
	else if (mBB.top() + vel.y > W_max.y)
		T.y = W_max.y-mBB.top();
	else
		T.y += vel.y;
	
	//Note the Z inversion...	
	if (mBB.near() + vel.z > W_min.z)
		T.z = W_min.z-mBB.near();
	else if (mBB.far() + vel.z < W_max.z)
		T.z = W_max.z - mBB.far();
	else
		T.z += vel.z;
	
	translate(T);

	return T;
}
