#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#define IMG "hello_world.png"
#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 700

using namespace std;

SDL_Window * gWindow=NULL;
SDL_Renderer * gRenderer=NULL;
TTF_Font * gFont = NULL;

class LTexture
{
   public:
      LTexture();
      ~LTexture();
      bool loadFromFile(std::string path);
      bool loadFromRenderedText(std::string texText,SDL_Color textColor);
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

LTexture gTextTexture;

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

   if (TTF_Init()<0){
      cout << TTF_GetError() << endl;
      return false;
   }
   
   return true;
}

bool loadMedia(){
   gFont=TTF_OpenFont("lazy.ttf",28); 
   if (gFont==NULL){
      cout << TTF_GetError() << endl;
      return false;
   }

   SDL_Color textColor = {0, 0, 0};
   if (!gTextTexture.loadFromRenderedText("fuck you asshole",textColor)){
      cout << "failure" << endl;
      return false;
   }

   return true;
}

void close(){
   gTextTexture.free();

   TTF_CloseFont(gFont);
   gFont=NULL;
   
   SDL_DestroyRenderer(gRenderer);
   SDL_DestroyWindow(gWindow);
   gRenderer=NULL;
   gWindow=NULL;

   TTF_Quit();
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
	 if (e.type==SDL_QUIT){
	    quit=true;
	 }
	 SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	 SDL_RenderClear( gRenderer );
      
	 gTextTexture.render((SCREEN_WIDTH-gTextTexture.getWidth())/2,
			     (SCREEN_HEIGHT-gTextTexture.getHeight())/2);

	 SDL_RenderPresent( gRenderer );
      }
   }
   close();
   return 1;
}
