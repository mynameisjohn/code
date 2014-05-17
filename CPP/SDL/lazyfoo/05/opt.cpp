#include <SDL2/SDL.h>
#include <iostream>

#define IMG "hello_world.bmp"
#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 700

enum KeyPressSurfaces{
   KEY_PRESS_SURFACE_DEFAULT, 
   KEY_PRESS_SURFACE_UP, 
   KEY_PRESS_SURFACE_DOWN, 
   KEY_PRESS_SURFACE_LEFT, 
   KEY_PRESS_SURFACE_RIGHT, 
   KEY_PRESS_SURFACE_TOTAL 
};

using namespace std;

SDL_Window * gWindow=NULL;
SDL_Surface * gScreenSurface=NULL;
SDL_Surface * gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL]; //=NULL;
SDL_Surface * gCurrentSurface=NULL;

SDL_Surface * loadSurface(string path){
   SDL_Surface * tmp = SDL_LoadBMP(path.c_str()), * surface;
   if (tmp==NULL)
      cout << SDL_GetError() << endl;
  
   surface=SDL_ConvertSurface(tmp,gScreenSurface->format, NULL);
   if (surface==NULL)
      cout << SDL_GetError() << endl;
   
   SDL_FreeSurface(tmp);

   return surface;
}

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
   gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = 
      loadSurface("press.bmp");
   gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] =
      loadSurface("up.bmp");
   gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] =
      loadSurface("down.bmp");
   gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] =
      loadSurface("left.bmp");
   gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] =
      loadSurface("right.bmp");

   for (int i=0;i<KEY_PRESS_SURFACE_TOTAL;i++)
      if (gKeyPressSurfaces[i]==NULL)
	 return false;

   return true;
}

void close(){
   for (int i=0;i<KEY_PRESS_SURFACE_TOTAL;i++){
      gKeyPressSurfaces[i]=NULL;
   }  
 
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

   gCurrentSurface=gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
   
   while (!quit){
      while (SDL_PollEvent(&e)!=0){
	 if (e.type==SDL_QUIT)
	    quit=true;
	 else if (e.type==SDL_KEYDOWN){
	    switch(e.key.keysym.sym)
	    {
	       case SDLK_UP:
		  gCurrentSurface=gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
		  break;
	       case SDLK_DOWN:
                  gCurrentSurface=gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                  break;
               case SDLK_LEFT:
                  gCurrentSurface=gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                  break;
               case SDLK_RIGHT:
                  gCurrentSurface=gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                  break;
               default:
                  gCurrentSurface=gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
                  break;
	    }
	    SDL_Rect stretched;
	    stretched.x=0; stretched.y=0;
	    stretched.w=SCREEN_WIDTH; stretched.h=SCREEN_HEIGHT;
	    SDL_BlitScaled( gCurrentSurface, NULL, gScreenSurface, &stretched );
	    SDL_UpdateWindowSurface(gWindow);
	 }
      }
   }
   close();
   return 1;
}
