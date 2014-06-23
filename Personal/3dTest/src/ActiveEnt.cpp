#include "ActiveEnt.h"

void ActiveEnt::setColBufVec(std::vector<colBuf> cBufVec){
	mCBufs = cBufVec;
}

ActiveEnt::ActiveEnt() : Entity(){
	mVel = glm::vec3();
	mSpeed = 4;
}

ActiveEnt::ActiveEnt(Collider c) : Entity(c){
	//NYI
}
