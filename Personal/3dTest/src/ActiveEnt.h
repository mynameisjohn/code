#ifndef ACTIVEENT_H
#define ACTIVEENT_H

#include "Entity.h"
#include <stdio.h>

class ActiveEnt: public Entity{
	public:
		ActiveEnt();
		ActiveEnt(Collider c);
		virtual void update(){};//NYI
		void moveWRT_walls();
		void moveWRT_ent(Entity& e);
		virtual void move(){};
		void moveToEdge(int, Entity&);
	protected:
		vec3 mVel;
		vec3 mSpeed;
		bool grounded;
};

#endif
