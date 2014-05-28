#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "JShader.h"
#include "Drawable.h"

typedef struct shadeCollective{
	JShader shader;
	std::vector<Drawable> dr;
} shadeCollective;

bool initGL();

bool initGeom(Drawable * dr, std::string src, float x, float y);

void update();

void handleEvent(SDL_Event& e);

void render();

void move();

void closeShader();

void showColliders(SDL_Renderer * renderer);
