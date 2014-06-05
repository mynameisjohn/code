#ifndef ENTITY_H
#define ENTITY_H

//Do I really need GLM?
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <vector>
#include "Collider.h"
#include "iRect.h"

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
		void move(std::vector<Entity>& entities);
		glm::vec3 getTranslate();
	protected:
		Collider mCollider;
		glm::vec3 mTranslate;
		glm::vec3 mPos;
		int mVelX, mVelY, mSpeed;
		bool xFirst;
};

#endif
