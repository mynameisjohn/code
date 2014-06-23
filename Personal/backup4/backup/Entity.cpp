#include "Entity.h"
#include <stdio.h>
#include <time.h>

Entity::Entity(){
	mTranslate = {0, 0, 0};
	mPos = glm::vec3();
	mVelX = 0;
	mVelY = 0;
	mSpeed = 5;
	steppedOn = false;
}

Entity::~Entity(){
	//What should I do here?
}

Collider * Entity::getCollider(){
	return &mCollider;
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

void Entity::move(std::vector<Entity>& entities, std::vector<Collider>& scenery){
	int oldX, oldY;
	mCollider.move(mVelX, mVelY, oldX, oldY);
	//Now handle other entities and scenery
	int i=0;


	std::vector<Collider>::iterator colIter;
	for (colIter=scenery.begin(); colIter!=scenery.end(); colIter++){
		bool colX = mCollider.overlaps_X(&(*colIter));
		bool colY = mCollider.overlaps_Y(&(*colIter));
		
		if (colX && colY){
			int newX=-1, newY=-1;
			if (xFirst[i]){
				if (mVelY<0)
					newY = colIter->getTopBottom();
				else if (mVelY>0)
					newY = colIter->getTopTop()-mCollider.getTop_h();
			}
			else{
				if (mVelX<0)
					newX = colIter->getTopRight(); 
				else if (mVelX>0)
					newX = colIter->getTopLeft()-mCollider.getTop_w();
			}
			mCollider.moveTo(newX, newY);
		}
		else
			xFirst[i] = colX && !colY;

		i++;
	}

	std::vector<Entity>::iterator eIter;
	for (eIter=entities.begin(); eIter!=entities.end(); eIter++){
		if (!(&(*this) == &(*eIter))){//if this entity ain't us
			if (this->collidesWith(eIter)){
				//do something, maybe print?
				
				//fprintf(stdout, "ITS %u\n O CLOCK READ IT GET OUT\n", (unsigned)time(NULL));
			}
		}
	}

	mTranslate = mCollider.diff(oldX, oldY); 
}

bool Entity::collidesWith(std::vector<Entity>::iterator eIt){
	if ((this->mCollider.collidesWith(eIt->getCollider()))){//only tops for now
		//eIt->steppedOn = true;
		return true;
	}
	else{
		//eIt->steppedOn = false;
		return false;
	}
}

void Entity::step(){
	steppedOn = !steppedOn;
}

bool Entity::isSteppedOn(){
	return steppedOn;
}

//handle per entity collision next

void Entity::setWalls(int x, int y, int X, int Y){
	mCollider.setWalls(x, y, X, Y);
}

glm::vec3 Entity::getTranslate(){
	return mTranslate;
}

void Entity::setXFirst(std::vector<bool> new_xFirst){
	xFirst = new_xFirst;
}
