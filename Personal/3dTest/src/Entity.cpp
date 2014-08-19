#include "Entity.h"

Entity::Entity(){
	mPos = glm::vec3();
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

void Entity::translate(glm::vec3 t){
	this->translate(t.x, t.y, t.z);
}

void Entity::translate(int tX, int tY, int tZ){
	mPos.x+=(float) tX;
	mPos.y+=(float) tY;
	mPos.z+=(float) tZ;
	
	mCollider.translate(tX, tY, tZ);
}

char Entity::collidesWith(Entity& e){
	char last = mCollider.collidesWith(e.mCollider);
	return last;
}

bool Entity::overlapsWith(Entity& e){
	return mCollider.overlapsWith(e.mCollider);
}

//This will have to change
glm::vec3 Entity::getPos(){
	return mPos;
}
