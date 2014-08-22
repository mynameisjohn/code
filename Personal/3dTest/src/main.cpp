#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL_thread.h>
#include "BaseFunc.h"

#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 480


bool init();
void close();

SDL_Window * gWindow;
SDL_GLContext gContext;

int main(int argc, char ** argv){
	//Initialize Everything
	if (!init()){
	   printf( "Failed to initialize!\n" );
      return EXIT_FAILURE;
   }

	//polling boolean, key event, sub thread
	bool quit = false;
	SDL_Event e;
	SDL_Thread * subThread = NULL;

	//main event loop
	while (!quit){
		while (SDL_PollEvent(&e) != 0){
			if (e.type == SDL_QUIT)
				quit = true;
			handleEvent(e);
		}
		move();
		update(NULL);
		///SDL_CreateThread(update, "Update Thread", NULL);
		render();
		//SDL_WaitThread(subThread, NULL);
		SDL_GL_SwapWindow(gWindow);
	}
	close();

	return EXIT_SUCCESS;
}

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
   gWindow = SDL_CreateWindow("3D Test",
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
   if(!initGL()){
      printf( "Unable to initialize OpenGL!\n" );
      return false;
   }

   return true;
}

void close(){
	closeShader();
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	SDL_Quit();
}
