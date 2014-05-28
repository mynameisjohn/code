#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "JShader.h"
#include "Player.h"

typedef struct shadeCollective{
	JShader shader;
	std::vector<Drawable> dr;
} shadeCollective;

bool initGL();

bool initGeom(Drawable * dr, std::string src, int x, int y);

void update();

void handleEvent(SDL_Event& e);

void render();

void move();

void closeShader();

void showColliders(SDL_Renderer * renderer);

bool collision();
