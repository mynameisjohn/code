#include "Entity.h"

Entity::Entity(){
	mTranslate = glm::vec3();
	mPos = glm::vec3();
	mVelX = 0;
	mVelY = 0;
	mSpeed = 10;
	xFirst = false;
}

Entity::~Entity(){
	//What should I do here?
}

void Entity::setSpeed(int speed){
	mSpeed = speed;
}

void Entity::moveTo(glm::vec3 dest){
	mTranslate = dest;
	//Do something with collider
}

void Entity::translate(glm::vec3 translate){
	mPos += translate;
	//Do something with collider
}

void Entity::setTop(iRect top){
	mCollider.setTop(top);
}

void Entity::addSub(iRect sub){
	mCollider.addSub(sub);
}

void Entity::update(){
	//NYI
}

void Entity::move(std::vector<Entity>& entities){
	mTranslate = mCollider.move(mVelX, mVelY);
}

//handle per entity collision next

void Entity::setWalls(int x, int y, int X, int Y){
	mCollider.setWalls(x, y, X, Y);
}

glm::vec3 Entity::getTranslate(){
	return mTranslate;
}
