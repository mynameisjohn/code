#include "ActiveEnt.h"

ActiveEnt::ActiveEnt() : Entity(){
	mVel = vec3();
	mSpeed = vec3(40.f, 40.f, 20.12241f);
	speedOsc=0.f;
}

ActiveEnt::ActiveEnt(Collider c) : Entity(c){
	//NYI
}

void ActiveEnt::update(){
	mVel.x = (float)mSpeed.x*sin(speedOsc);
	//printf("%lf\n",mVel.x);
	speedOsc+=0.1f;	
//NYI
}

void ActiveEnt::moveWRT_walls(){
	mTrans = mCollider.move(mVel);
}

vec3 ActiveEnt::getVel(){
	return mVel;
}

/* The goal here is to find the direction in which the last collision
(bounding box violation) occurred, so that the entity can translate
right up against it.*/
void ActiveEnt::moveWRT_ent(Entity * e){
	char last = collidesWith(e);

	switch (last){
		case 'x':
			if (mVel.x > 0)
            translate(vec3(toLeft(e), 0, 0));
         else if (mVel.x < 0)
            translate(vec3(toRight(e), 0, 0));
			break;
		case 'y':
			if (mVel.y < 0){
            translate(vec3(0,toTop(e), 0));
				mCollider.ground();// = true;
			}
         else if (mVel.y > 0)
            translate(vec3(0, toBottom(e), 0));
			break;

		case 'z':
			if (mVel.z > 0)
            translate(vec3(0, 0, toFar(e)));
         else if (mVel.z < 0)
            translate(vec3(0, 0, toNear(e)));
			break;

		default:
			break;
	}	
}
