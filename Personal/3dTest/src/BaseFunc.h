#include "Drawable.h"
#include <SDL2/SDL.h>

bool initGL();

bool initLevel();

Drawable initQuad();

int update(void * data);

void move();

void closeShader();

void handleEvent(SDL_Event& e);

void render();

void initPlayer();

void initObstacle(int x, int y);
