//I ripped this off of lazyfoo. Thanks. 

/*
TODO:
	+ Make Drawable more Abstract
		- Enumerations for Player, Scenery, Enemies, Projectiles
	+ Use sub-colliders during collision
	+ Move collision handling out of Drawable
	+ Handle different types of collisions (wall, projectile)
	+ Test a more complex model
		- Figure out indexing
		- Figure out skinning
	+ Array Buffer Objects + Textures
	+ Split up update/render threads
		- Figure out a way of using semaphores
*/

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_opengl.h>
#include <stdio.h>

#include "BaseFunc.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

//Initializes the window and OpenGL context
//then passes the torch to BaseFunc
bool init();

//closes things
void close();

//Window and GL context
SDL_Window * gWindow;
SDL_GLContext gContext;
SDL_Renderer * gRenderer;

bool drawCols=true;

int main(int argc, char** argv)
{
	//Start up SDL and create window
	if(!init()){
		printf( "Failed to initialize!\n" );
		return false;
	}
	
	bool quit = false;
	SDL_Event e;
	
	while (!quit){
		while (SDL_PollEvent(&e) != 0){
			if (e.type == SDL_QUIT)
				quit = true;
			handleEvent(e);
		}
		update();
		render();
		if (drawCols)
         showColliders(gRenderer);
		SDL_GL_SwapWindow(gWindow);
	}
	close();

	return 1;
}

//SDL seems to cry if the window/context isn't global
bool init(){
   //Init SDL Video
   if (SDL_Init( SDL_INIT_VIDEO ) < 0){
      printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
      return false;
   }
   //Init SDL+OpenGL Context
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
   //Create Window
   gWindow = SDL_CreateWindow("SDL Tutorial",
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
   if (gWindow == NULL){
      printf( "Window could not be created! SDL Error: %s\n", SDL_GetError());
      return false;
   }

   //Create Context from Window
   gContext = SDL_GL_CreateContext(gWindow);
   if( gContext == NULL ){
      printf("OpenGL context was not created! SDL Error: %s\n", SDL_GetError());
      return false;
   }

   //Initialize GLEW
   glewExperimental = GL_TRUE;
   GLenum glewError = glewInit();
   if( glewError != GLEW_OK ){
      printf( "Error initializing GLEW! %s\n", glewGetErrorString(glewError));
      return false;
   }
   //Use Vsync
   if( SDL_GL_SetSwapInterval(1) < 0 ){
      printf( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
   }
   //Initialize OpenGL
   if( !initGL()){
      printf( "Unable to initialize OpenGL!\n" );
      return false;
   }
 
	return true;
}


void close(){
   //Deallocate program
	closeShader();
   //Destroy window  
   SDL_DestroyWindow( gWindow );
   gWindow = NULL;
   //Quit SDL subsystems
   SDL_Quit();
}

