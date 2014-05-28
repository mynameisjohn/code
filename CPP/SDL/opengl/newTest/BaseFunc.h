#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>
#include "JShader.h"
#include "Drawable.h"

#define VERT_SHADER "shaders/simpleVert.glsl"
#define FRAG_SHADER "shaders/simpleFrag.glsl"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

typedef struct ShadeCollective{
	JShader shader;
	std::vector<Drawable> drawables;
} ShadeCollective;

//Starts up SDL, creates window, and initializes OpenGL
bool init(SDL_Window * mWindow, SDL_GLContext * mCtx);

//Initializes rendering program and clear color
bool initGL();

//Initialize Simple Geometry
void initGeom(Drawable * square);

//Input handler
void handleKeys( unsigned char key, int x, int y );

//Per frame update
void update();

//Renders quad to the screen
void render();

//Frees media and shuts down SDL
void closeGL();
