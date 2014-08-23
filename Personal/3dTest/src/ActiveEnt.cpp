#include "ActiveEnt.h"

ActiveEnt::ActiveEnt() : Entity(){
	mVel = vec3();
	mSpeed = vec3(40.f, -40.f, 20.12241f);
}

ActiveEnt::ActiveEnt(Collider c) : Entity(c){
	//NYI
}

void ActiveEnt::moveWRT_walls(){
	grounded = mCollider.move(mVel);
}

void ActiveEnt::moveWRT_ent(Entity& e){
	char last = collidesWith(e);
	switch (last){
		case 'x':
			if (mVel.x > 0)
            translate(vec3(toLeft(e), 0, 0));
         else if (mVel.x < 0)
            translate(vec3(toRight(e), 0, 0));
			break;
		case 'y':
			if (mVel.y > 0){
            translate(vec3(0,toTop(e), 0));
				grounded = true;
			}
         else if (mVel.y < 0)
            translate(vec3(0, toBottom(e), 0));
			break;

		case 'z':
			if (mVel.z > 0)
            translate(vec3(0, 0, toNear(e)));
         else if (mVel.z < 0)
            translate(vec3(0, 0, toFar(e)));
			break;

		default:
			break;
	}	
}
/*
void ActiveEnt::moveToEdge(int last, Entity& e){
	switch (last){
		case 1:
			if (mVel.x > 0)
				translate(toLeft(e), 0, 0);
			else if (mVel.x < 0)
            translate(toRight(e), 0, 0);
			break;

		case 2:
         if (mVel.y < 0)
            translate(0, toBottom(e), 0);
         else if (mVel.y > 0)
            translate(0, toTop(e), 0);
         break;

		case 4:
         if (mVel.z > 0)
            translate(0, 0, toNear(e));
         else if (mVel.z < 0)
            translate(0, 0, toFar(e));
         break;
	}
}
*/
