#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

#include "Drawable.h"

class Player : public Entity{
	public:
		void handleEvent(SDL_Event& e);
};

#endif
