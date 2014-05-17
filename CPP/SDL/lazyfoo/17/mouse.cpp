#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_ttf.h>
#include <iostream>

#define IMG "hello_world.png"
#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 700

#define BUTTON_WIDTH 300
#define BUTTON_HEIGHT 200
#define TOTAL_BUTTONS 4

enum LButtonSprite
{
   BUTTON_SPRITE_MOUSE_OUT = 0, 
   BUTTON_SPRITE_MOUSE_OVER_MOTION = 1, 
   BUTTON_SPRITE_MOUSE_DOWN = 2, 
   BUTTON_SPRITE_MOUSE_UP = 3, 
   BUTTON_SPRITE_TOTAL = 4 
};

using namespace std;

SDL_Window * gWindow=NULL;
SDL_Renderer * gRenderer=NULL;
SDL_Rect gSpriteClips[ BUTTON_SPRITE_TOTAL ];

class LTexture
{
   public:
      LTexture();
      ~LTexture();
      bool loadFromFile(std::string path);
	 #ifdef _SDL_TTF_H
	 bool loadFromRenderedText(std::string texText,SDL_Color textColor);
	 #endif
      void free();
      void render(int x, int y, SDL_Rect * clip=NULL, double angle=0, 
		  SDL_Point* center=NULL, SDL_RendererFlip flip=SDL_FLIP_NONE);
      int getWidth();
      int getHeight();
      void setColor(Uint8 red, Uint8 green, Uint8 blue);
      void setBlendMode(SDL_BlendMode blend);
      void setAlpha(Uint8 alpha);
   private:
      SDL_Texture * mTexture;
      int mWidth;
      int mHeight;
};

class LButton
{
   public:
      LButton();
      void setPosition(int x, int y);
      void handleEvent(SDL_Event * e);
      void render();
   private:
      SDL_Point mPosition;
      LButtonSprite mCurrentSprite;
};

LTexture::LTexture(){
   mTexture=NULL;
   mWidth=0;
   mHeight=0;
}

LTexture::~LTexture(){
   free();
}

void LTexture::setBlendMode(SDL_BlendMode blend){
   SDL_SetTextureBlendMode(mTexture,blend);
}

void LTexture::setAlpha(Uint8 alpha){
   SDL_SetTextureAlphaMod(mTexture,alpha);
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue){
   SDL_SetTextureColorMod(mTexture,red,green,blue);
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

void LTexture::render(int x, int y, SDL_Rect * clip,
		     double angle, SDL_Point * center, SDL_RendererFlip flip){
   SDL_Rect renderQuad = {x, y, mWidth, mHeight};
   
   if (clip != NULL){
      renderQuad.w=clip->w;
      renderQuad.h=clip->h;
   }
   
   SDL_RenderCopyEx(gRenderer,mTexture,clip,&renderQuad,angle,center,flip);
}

int LTexture::getWidth(){
   return mWidth;
}

int LTexture::getHeight(){
   return mHeight;
}

#ifdef _SDL_TTF_H
bool LTexture::loadFromRenderedText(std::string texText, SDL_Color textColor){
   free();
   
   SDL_Surface * surface = TTF_RenderText_Solid(gFont,texText.c_str(),textColor);
   if (surface==NULL){
      cout << SDL_GetError() << endl;
      return false;
   }

   mTexture=SDL_CreateTextureFromSurface(gRenderer,surface);
   if (mTexture==NULL){
      cout << SDL_GetError() << endl;
      return false;
   }

   mWidth=surface->w;
   mHeight=surface->h;

   SDL_FreeSurface(surface);

   return mTexture != NULL;
}
#endif

LButton::LButton(){
   mPosition.x=0;
   mPosition.y=0;
   mCurrentSprite=BUTTON_SPRITE_MOUSE_OUT;
}

void LButton::setPosition(int x, int y){
   mPosition.x=x;
   mPosition.y=y;
}

void LButton::handleEvent(SDL_Event * e){
   if (e->type==SDL_MOUSEMOTION || 
      e->type==SDL_MOUSEBUTTONDOWN ||
      e->type==SDL_MOUSEBUTTONUP){
      int x, y;
      SDL_GetMouseState(&x,&y);
   
      bool inside=
      (x>mPosition.x) & (x<mPosition.x+BUTTON_WIDTH) &
      (y>mPosition.y) & (y<mPosition.y+BUTTON_HEIGHT);
      
      if (!inside)
	 mCurrentSprite=BUTTON_SPRITE_MOUSE_OUT;
      else{
	 switch(e->type){
	    case SDL_MOUSEMOTION: 
	       mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION; 
	       break; 
	    case SDL_MOUSEBUTTONDOWN: 
	       mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN; 
	       break; 
	    case SDL_MOUSEBUTTONUP: 
	       mCurrentSprite = BUTTON_SPRITE_MOUSE_UP; 
	       break;
	 }
      }
   }
}

LTexture gButtonSpriteSheetTexture;

void LButton::render(){
   gButtonSpriteSheetTexture.render(
      mPosition.x,mPosition.y,&gSpriteClips[mCurrentSprite]);
}

LButton gButtons[ TOTAL_BUTTONS ];

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

   gRenderer = SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED | 
					     SDL_RENDERER_PRESENTVSYNC);
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
   if(!gButtonSpriteSheetTexture.loadFromFile( "button.png")){
      cout << SDL_GetError() << endl;
      return false;
   }
   
   for (int i=0;i<BUTTON_SPRITE_TOTAL;++i){
      gSpriteClips[ i ].x = 0;
      gSpriteClips[ i ].y = i * 200;
      gSpriteClips[ i ].w = BUTTON_WIDTH;
      gSpriteClips[ i ].h = BUTTON_HEIGHT;
   }

   gButtons[ 0 ].setPosition( 0, 0 );
   gButtons[ 1 ].setPosition( SCREEN_WIDTH - BUTTON_WIDTH, 0 );
   gButtons[ 2 ].setPosition( 0, SCREEN_HEIGHT - BUTTON_HEIGHT );
   gButtons[ 3 ].setPosition( SCREEN_WIDTH - BUTTON_WIDTH, SCREEN_HEIGHT - BUTTON_HEIGHT );

   return true;
}

void close(){
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
   double deg=0;
   SDL_RendererFlip flipType=SDL_FLIP_NONE;

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
	 for (int i=0;i<TOTAL_BUTTONS;++i)
	    gButtons[ i ].handleEvent( &e );
      }	 
      SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
      SDL_RenderClear( gRenderer );
            
      for (int i=0;i<TOTAL_BUTTONS;++i)
      gButtons[i].render();

      SDL_RenderPresent( gRenderer );
   }
   close();
   return 1;
}
