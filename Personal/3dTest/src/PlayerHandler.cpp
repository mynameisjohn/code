#include <SDL2/SDL.h>

#include "PlayerHandler.h"

PlayerHandler::PlayerHandler() : KeyboardHandler(){
	//NYI
}

glm::vec3 PlayerHandler::getVel(){
	glm::vec3 vel;
	float dash = getKeyState(SDLK_LSHIFT) ? 1.f : 0.f;
	float jump = getKeyState(SDLK_SPACE) ? 1.f : 0.f;
	
	if (getKeyState(SDLK_w))
		vel.z -= 1.f;
	if (getKeyState(SDLK_s))
		vel.z+= 1.f;
	
	if (getKeyState(SDLK_a))
		vel.x -= 1.f+dash;
	if (getKeyState(SDLK_d))
		vel.x += 1.f+dash;
	
	vel.y = jump;

	return vel;
}
