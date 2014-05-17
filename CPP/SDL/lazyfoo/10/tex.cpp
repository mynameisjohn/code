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

class LTexture
{
   public:
      LTexture();
      ~LTexture();
      bool loadFromFile(std::string path);
      void free();
      void render(int x, int y);
      int getWidth();
      int getHeight();
   private:
      SDL_Texture * mTexture;
      int mWidth;
      int mHeight;
};

LTexture::LTexture(){
   mTexture=NULL;
   mWidth=0;
   mHeight=0;
}

LTexture::~LTexture(){
   free();
}

bool LTexture::loadFromFile(std::string path){
   free();
   SDL_Texture * texture = NULL;

   SDL_Surface * surface=IMG_Load(path.c_str());
   if (surface==NULL){
      cout << SDL_GetError() << endl;
      return false;
   }

   SDL_SetColorKey(surface,SDL_TRUE,
      SDL_MapRGB(surface->format,0x00,0xFF,0xFF));

   texture=SDL_CreateTextureFromSurface(gRenderer,surface);
   if (texture==NULL){
      cout << SDL_GetError() << endl;
      return false;
   }

   mWidth=surface->w;
   mHeight=surface->h;
   SDL_FreeSurface(surface);
 
   mTexture=texture;

   return mTexture != NULL;
}

void LTexture::free(){
   if (mTexture != NULL){
      SDL_DestroyTexture(mTexture);
      mTexture=NULL;
      mWidth=0;
      mHeight=0;
   }
}

void LTexture::render(int x, int y){
   SDL_Rect renderQuad = {x, y, mWidth, mHeight};
   SDL_RenderCopy(gRenderer,mTexture,NULL,&renderQuad);
}

int LTexture::getWidth(){
   return mWidth;
}

int LTexture::getHeight(){
   return mHeight;
}

LTexture gFooTexture, gBackgroundTexture;

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
   if (!gFooTexture.loadFromFile("foo.png")){
      cout << SDL_GetError() << endl;
      return false;
   }
   
   if (!gBackgroundTexture.loadFromFile("background.png")){
      cout << SDL_GetError() << endl;
      return false;
   }

   return true;
}

void close(){
   gFooTexture.free();
   gBackgroundTexture.free();
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

	 gBackgroundTexture.render(0,0);
	 gFooTexture.render(240,190);

	 SDL_RenderPresent(gRenderer);
      }
   }
   
   close();
   return 1;
}
