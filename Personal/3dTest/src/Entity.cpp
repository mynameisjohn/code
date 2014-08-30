#include "Entity.h"
#include <glm/gtx/transform.hpp>

Entity::Entity(){
	mDrawables.clear();
};

Entity::Entity(Collider c){
	mCollider = c;
}

void Entity::draw(int MVHandle, int ColorHandle){
	std::vector<Drawable>::iterator drIt;
	for (drIt=mDrawables.begin(); drIt!=mDrawables.end(); drIt++){
//		drIt->leftMultMV(glm::translate(mTrans));
		drIt->draw(MVHandle, ColorHandle, getPos());
	}
/*
	mDrawable.leftMultMV(glm::translate(mTrans));
	mDrawable.draw(MVHandle, ColorHandle);
*/
}

void Entity::addDrawable(Drawable dr){
	mDrawables.push_back(dr);// = dr;
}

void Entity::setCol(Collider c){
	mCollider = c;
}

void Entity::setBB(BoundBox bb){
	mCollider.setBB(bb);
}

char Entity::collidesWith(Entity * e){
	char last = mCollider.collidesWith(e->getCol());
	return last;
}

bool Entity::overlapsWith(Entity * e){
	return mCollider.overlapsWith(e->getCol());
}

void Entity::translate(vec3 trans){
	mTrans += trans;
	mCollider.translate(trans); 
} 
vec3 Entity::getPos(){ 
	return mCollider.getPos(); 
} 
float Entity::toLeft(Entity * e){ 
	return mCollider.toLeft(e->getCol()); 
} 
float Entity::toRight(Entity * e){ 
	return mCollider.toRight(e->getCol()); 
} 
float Entity::toBottom(Entity * e){ 
	return mCollider.toBottom(e->getCol()); 
} 
float Entity::toTop(Entity * e){ 
	return mCollider.toTop(e->getCol()); 
} 
float Entity::toNear(Entity * e){ 
	return mCollider.toNear(e->getCol()); 
} 
float Entity::toFar(Entity * e){ 
	return mCollider.toFar(e->getCol()); 
} 

Collider * Entity::getCol(){
	return &mCollider;
}

vec3 Entity::center(){ 
	return mCollider.center(); 
}
