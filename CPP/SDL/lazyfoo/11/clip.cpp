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
SDL_Rect gSpriteClips[4];
class LTexture
{
   public:
      LTexture();
      ~LTexture();
      bool loadFromFile(std::string path);
      void free();
      void render(int x, int y, SDL_Rect * clip);
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

void LTexture::render(int x, int y, SDL_Rect * clip){
   SDL_Rect renderQuad = {x, y, mWidth, mHeight};
   
   if (clip != NULL){
      renderQuad.w=clip->w;
      renderQuad.h=clip->h;
   }
   
   SDL_RenderCopy(gRenderer,mTexture,clip,&renderQuad);
}

int LTexture::getWidth(){
   return mWidth;
}

int LTexture::getHeight(){
   return mHeight;
}

LTexture gSpriteSheetTexture;

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
   if (!gSpriteSheetTexture.loadFromFile("dots.png")){
      cout << SDL_GetError() << endl;
      return false;
   }
   
   gSpriteClips[ 0 ].x = 0;
   gSpriteClips[ 0 ].y = 0;
   gSpriteClips[ 0 ].w = 100;
   gSpriteClips[ 0 ].h = 100;

   gSpriteClips[ 1 ].x = 100;
   gSpriteClips[ 1 ].y = 0;
   gSpriteClips[ 1 ].w = 100;
   gSpriteClips[ 1 ].h = 100;

   gSpriteClips[ 2 ].x = 0;
   gSpriteClips[ 2 ].y = 100;
   gSpriteClips[ 2 ].w = 100;
   gSpriteClips[ 2 ].h = 100;

   gSpriteClips[ 3 ].x = 100;
   gSpriteClips[ 3 ].y = 100;
   gSpriteClips[ 3 ].w = 100;
   gSpriteClips[ 3 ].h = 100;

   return true;
}

void close(){
   gSpriteSheetTexture.free();
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

	 gSpriteSheetTexture.render(0,0,&gSpriteClips[0]);
	 gSpriteSheetTexture.render(SCREEN_WIDTH-gSpriteClips[1].w,0,&gSpriteClips[1]);
	 gSpriteSheetTexture.render(0,SCREEN_HEIGHT-gSpriteClips[2].h,&gSpriteClips[2]);
	 gSpriteSheetTexture.render(SCREEN_WIDTH - gSpriteClips[ 3 ].w, SCREEN_HEIGHT - gSpriteClips[ 3 ].h, &gSpriteClips[ 3 ]);

	 SDL_RenderPresent(gRenderer);
      }
   }
   
   close();
   return 1;
}
