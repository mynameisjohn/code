#ifndef PLAYERHANDLER_H
#define PLAYERHANDLER_H

#ifndef GLM_FORCE_RADIANS 
#define GLM_FORCE_RADIANS 
#endif

#include <glm/glm.hpp>

#include "KeyboardHandler.h"

class PlayerHandler : public KeyboardHandler{
public:
	PlayerHandler();
	glm::vec3 getVel();
};

#endif
