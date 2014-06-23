#ifndef ENTITY_H
#define ENTITY_H

#include "Collider.h"

class Entity{
	public:
		Entity();
		Entity(Collider c);
		void setCol(Collider c);
		void setBB(BoundBox bb);
		void translate(int, int, int);
		bool collidesWith(Entity& e);
		bool overlapsWith(Entity& e);
		glm::vec3 getPos();
	protected:
		Collider mCollider;
		glm::vec3 mPos;
};


#endif
