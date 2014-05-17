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
   if( gWindow == NULL ){
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
	 if (e.type==SDL_QUIT){
	    quit=true;
	 }
	 
	 SDL_SetRenderDrawColor(gRenderer,0xFF,0xFF,0xFF,0xFF);
	 SDL_RenderClear(gRenderer);

	 SDL_Rect topRightViewPort,topLeftViewPort,bottomViewPort;
	 topRightViewPort.x=SCREEN_WIDTH/2;
	 topRightViewPort.y=0;
	 topRightViewPort.h=SCREEN_HEIGHT/2;
	 topRightViewPort.w=SCREEN_WIDTH/2;

	 topLeftViewPort.x=0;
         topLeftViewPort.y=0;
         topLeftViewPort.h=SCREEN_HEIGHT/2;
         topLeftViewPort.w=SCREEN_WIDTH/2;

	 bottomViewPort.x=0;
         bottomViewPort.y=SCREEN_HEIGHT/2;
         bottomViewPort.h=SCREEN_HEIGHT;
         bottomViewPort.w=SCREEN_WIDTH;

	 SDL_RenderSetViewport( gRenderer, &topRightViewPort);
	 SDL_RenderCopy(gRenderer,gTexture,NULL,NULL);

	 SDL_RenderSetViewport(gRenderer,&topLeftViewPort);
         SDL_RenderCopy(gRenderer,gTexture,NULL,NULL);

	 SDL_RenderSetViewport(gRenderer,&bottomViewPort);
         SDL_RenderCopy(gRenderer,gTexture,NULL,NULL);

	 SDL_RenderPresent(gRenderer);
      }
   }
   
   close();
   return 1;
}
