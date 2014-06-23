#include "Drawable.h"
#include <SDL2/SDL.h>

bool initGL();

bool initLevel();

Drawable initQuad();

void update();

void move();

void closeShader();

void handleEvent(SDL_Event& e);

void render();
