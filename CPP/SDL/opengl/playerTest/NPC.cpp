#include "NPC.h"

NPC::NPC(){
	theta=0.f;
	dTheta=.05f;
	A=100.f;
}

void NPC::update(){
	mVelY = A*cos(theta);

	theta += dTheta;
	if (theta > 2.f*M_PI)
		theta=0.f;
}

void NPC::handleEvent(SDL_Event& e){
//none
}
