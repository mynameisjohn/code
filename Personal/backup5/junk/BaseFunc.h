#ifndef BASEFUNC_H
#define BASEFUNC_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>

#include "Drawable.h"

bool initGL();

bool initSquare(Drawable * dr, int x, int y);

bool initRect(Drawable * dr, int x, int y);

bool initLevel();

bool initSquare(Drawable * dr, int x, int y);

bool initRect(Drawable * dr, int x, int y);

void update();

void move();

void handleEvent(SDL_Event& e);

void render();

void closeShader();



#endif
