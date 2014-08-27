#include "Entity.h"

Entity::Entity(){
	//NYI
};

Entity::Entity(Collider c){
	mCollider = c;
}

void Entity::setCol(Collider c){
	mCollider = c;
}

void Entity::setBB(BoundBox bb){
	mCollider.setBB(bb);
}

char Entity::collidesWith(Entity& e){
	char last = mCollider.collidesWith(e.mCollider);
	return last;
}

bool Entity::overlapsWith(Entity& e){
	return mCollider.overlapsWith(e.mCollider);
}

void Entity::translate(vec3 trans){ 
	mCollider.translate(trans); 
} 
vec3 Entity::getPos(){ 
	return mCollider.getPos(); 
} 
float Entity::toLeft(Entity& e){ 
	return mCollider.toLeft(e.mCollider); 
} 
float Entity::toRight(Entity& e){ 
	return mCollider.toRight(e.mCollider); 
} 
float Entity::toBottom(Entity& e){ 
	return mCollider.toBottom(e.mCollider); 
} 
float Entity::toTop(Entity& e){ 
	return mCollider.toTop(e.mCollider); 
} 
float Entity::toNear(Entity& e){ 
	return mCollider.toNear(e.mCollider); 
} 
float Entity::toFar(Entity& e){ 
	return mCollider.toFar(e.mCollider); 
} 
vec3 Entity::center(){ 
	return mCollider.center(); 
}
