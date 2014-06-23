#ifndef ACTIVEENT_H
#define ACTIVEENT_H

#include "Entity.h"
#include "ColBuf.h"
#include <stdio.h>

class ActiveEnt: public Entity{
	public:
		ActiveEnt();
		ActiveEnt(Collider c);
		void setColBufVec(std::vector<colBuf> cBufVec);
		virtual void update()=0;//NYI
		virtual void move()=0;
	protected:
		glm::vec3 mVel;
		int mSpeed;
		std::vector<colBuf> mCBufs;
};

#endif
