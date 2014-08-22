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
