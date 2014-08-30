#ifndef ACTIVEENT_H
#define ACTIVEENT_H

#include "Entity.h"
#include <stdio.h>

class ActiveEnt: public Entity{
	public:
		ActiveEnt();
		ActiveEnt(Collider c);
		void update();//NYI
		void moveWRT_walls();
		void moveWRT_ent(Entity * e);
		//virtual void move();//Make this pure asap
		vec3 getVel();
	protected:
		vec3 mVel; //Active velocity
		vec3 mSpeed; //Individual speed
		bool grounded; //Whether it's on top of something
		float speedOsc;
};

#endif
