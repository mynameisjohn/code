#ifndef ENTITY_H
#define ENTITY_H

//Do I really need GLM?
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <vector>
#include "Collider.h"
#include "iRect.h"

#define TYPE_PLAYER 1
#define TYPE_ENEMY 2
#define TYPE_INANIMATE 4
#define TYPE_ITEM 8
#define TYPE_AOE 16

class Collider;

class Entity{
	public:
		Entity();
		~Entity();
		void setSpeed(int speed);
		void moveTo(glm::vec3 dest);
		void translate(glm::vec3 translate);
		void setWalls(int x, int y, int X, int Y); 
		void setTop(iRect top);
		void addSub(iRect sub);
		void update();
		void move(std::vector<Entity>& entities, std::vector<Collider>& scenery);
		glm::vec3 getTranslate();
		void setXFirst(std::vector<bool> new_xFirst);
		bool collidesWith(std::vector<Entity>::iterator);
	protected:
		Collider mCollider;
		glm::vec3 mTranslate;
		glm::vec3 mPos;
		std::vector<bool> xFirst;
		int mVelX, mVelY, mSpeed;
		int mStatus;
};

#endif
