#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#define IMG "hello_world.png"
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
SDL_Renderer * gRenderer=NULL;
SDL_Texture * gTexture = NULL;

SDL_Texture * loadTexture(string path){
   SDL_Texture * texture = NULL;

   SDL_Surface * surface = IMG_Load(path.c_str());
   if (surface==NULL)
      cout << SDL_GetError() << endl;

   texture = SDL_CreateTextureFromSurface(gRenderer,surface);
   if (texture==NULL)
      cout << SDL_GetError() << endl;

   SDL_FreeSurface(surface);

   return texture;
}

bool init(){
   if (SDL_Init(SDL_INIT_VIDEO)<0){
      cout << SDL_GetError() << endl;
      return false;
   }

   gWindow=SDL_CreateWindow("SDL Tutorial", 
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
      SCREEN_WIDTH, SCREEN_HEIGHT, 
      SDL_WINDOW_SHOWN ); 
   if( gWindow == NULL ){
      cout << SDL_GetError() << endl;
      return false;
   }

   gRenderer = SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED);
   if( gRenderer == NULL ){
      cout << SDL_GetError() << endl;
      return false;
   }

   SDL_SetRenderDrawColor(gRenderer,0xFF,0xFF,0xFF,0xFF);

   int imgFlags=IMG_INIT_PNG;
   if (!(IMG_Init(imgFlags) & imgFlags)){
      cout << IMG_GetError() << endl;
      return false;
   }
   
   return true;
}

bool loadMedia(){
   gTexture = loadTexture("hello_world.png");
   if (gTexture==NULL){
      cout << SDL_GetError() << endl;
      return false;
   }
   
   return true;
}

void close(){
   SDL_DestroyTexture(gTexture);
   gTexture=NULL;
   SDL_DestroyRenderer(gRenderer);
   SDL_DestroyWindow(gWindow);
   gRenderer=NULL;
   gWindow=NULL;

   IMG_Quit();
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
      while (SDL_PollEvent(&e)!=0){
	 if (e.type==SDL_QUIT)
	    quit=true;
	 SDL_RenderClear(gRenderer);
	 SDL_RenderCopy(gRenderer,gTexture,NULL,NULL);
	 SDL_RenderPresent(gRenderer);
      }
   }
   
   close();
   return 1;
}
