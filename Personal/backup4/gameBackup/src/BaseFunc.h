#ifndef BASEFUNC_H
#define BASEFUNC_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>

#include "Drawable.h"

bool initGL();

bool initGeom(Drawable * dr, std::string src, int x, int y);

void update();

void move();

void handleEvent(SDL_Event& e);

void render();

void closeShader();

bool initSquare(Drawable& dr, int x, int y);

bool addSquare(int x, int y, int type);

#endif
