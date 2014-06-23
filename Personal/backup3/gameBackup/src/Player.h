#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

#include "KeyboardHandler.h"
#include "Drawable.h"

class Player : public Entity{
	public:
		void handleEvent(KeyboardHandler * handler);
};

#endif
