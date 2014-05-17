#include <SDL2/SDL.h>
#include <iostream>

#define IMG "hello_world.bmp"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

SDL_Window * gWindow=NULL;
SDL_Surface* gScreenSurface=NULL;
SDL_Surface* gHelloWorld=NULL;

using namespace std;

bool init(){
   bool success=true;

   if (SDL_Init(SDL_INIT_VIDEO)<0){
      cout << SDL_GetError() << endl;
      success=false;
      return success;
   }

   gWindow=SDL_CreateWindow("SDL Tutorial", 
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
      SCREEN_WIDTH, SCREEN_HEIGHT, 
      SDL_WINDOW_SHOWN ); 

   if( gWindow == NULL ){cout << SDL_GetError() << endl;
      success=false;
      return success;
   }

   gScreenSurface=SDL_GetWindowSurface(gWindow);

   return success;
}

bool loadMedia(){
   gHelloWorld=SDL_LoadBMP(IMG);
   if (gHelloWorld==NULL){
      cout << SDL_GetError() << endl;
      return false;
   }

   return true;
}

void close(){
   SDL_FreeSurface(gHelloWorld);
   gHelloWorld=NULL;
   
   SDL_DestroyWindow(gWindow);
   gWindow=NULL;

   SDL_Quit();
}

int main(int argc, char ** argv){
   bool quit=false;
   SDL_Event e;

   if (!init()){
      cout << "Failed to initialize" << endl;
      return -1;
   }

   if (!loadMedia()){
      cout << "Failed to load media" << endl;
      return -1;
   }
   
   while (!quit){
      while (SDL_PollEvent(&e)!=0)
	 if (e.type==SDL_QUIT)
	    quit=true;
      SDL_BlitSurface( gHelloWorld, NULL, gScreenSurface, NULL );
      SDL_UpdateWindowSurface(gWindow);
   }
   close();
   return 1;
}
