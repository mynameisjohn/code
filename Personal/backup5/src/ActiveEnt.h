#ifndef ACTIVEENT_H
#define ACTIVEENT_H

#include "Entity.h"
#include <stdio.h>

class ActiveEnt: public Entity{
	public:
		ActiveEnt();
		ActiveEnt(Collider c);
		virtual void update()=0;//NYI
		void moveWRT_walls();
		void moveWRT_ent(Entity& e);
		virtual void move()=0;
		void moveToEdge(int, Entity&);
	protected:
		glm::vec3 mVel;
		int mSpeed;
};

#endif
