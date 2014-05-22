#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

class LTexture{
   public:
      LTexture();
      ~LTexture();
      bool loadFromFile(std::string path);
      #ifdef _SDL_TTF_H
      bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
      #endif

      void free();
      void setColor(Uint8 red, Uint8 green, Uint8 blue);
      void setBlendMode(SDL_BlendMode blending);
      void setAlpha(Uint8 alpha);
      void render(int x, int y, SDL_Rect * clip=NULL,double angle=0.0, SDL_Point* center=NULL, SDL_RendererFlip flip=SDL_FLIP_NONE);
      int getWidth();
      int getHeight();
	private:
		SDL_Texture* mTexture;
		int mWidth, mHeight;
};

class Dot{
   public:
      static const int DOT_WIDTH=20;
      static const int DOT_HEIGHT=20;
      static const int DOT_VEL=25;
      Dot(int x, int y);
      void handleEvent(SDL_Event& e);
      void move(std::vector<SDL_Rect>& otherColliders);
      void render();
      std::vector<SDL_Rect>& getColliders();
   private:
      int mPosX, mPosY;
      int mVelX, mVelY;
      std::vector<SDL_Rect> mColliders;
      void shiftColliders();
};

SDL_Window * gWindow=NULL;
SDL_Renderer* gRenderer=NULL;
LTexture gDotTexture;

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
   SDL_Texture* newTexture=NULL;
   SDL_Surface* loadedSurface=IMG_Load(path.c_str());
   if (loadedSurface==NULL)
      std::cout << IMG_GetError() << std::endl;
   else{
      SDL_SetColorKey(loadedSurface,SDL_TRUE,SDL_MapRGB(loadedSurface->format,0,0xFF,0xFF));
      newTexture=SDL_CreateTextureFromSurface(gRenderer,loadedSurface);
      if (newTexture==NULL)
	 std::cout << IMG_GetError() << std::endl;
      else{
	 mWidth=loadedSurface->w;
	 mHeight=loadedSurface->h;
      }
      SDL_FreeSurface(loadedSurface);
   }
   mTexture=newTexture;
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

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue){
   SDL_SetTextureColorMod(mTexture,red,green,blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending){
   SDL_SetTextureBlendMode(mTexture,blending);
}

void LTexture::setAlpha(Uint8 alpha){
   SDL_SetTextureAlphaMod(mTexture,alpha);
}

void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip){
   SDL_Rect renderQuad = {x,y,mWidth,mHeight};
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

Dot::Dot(int x, int y){
	mPosX=x;
	mPosY=y;
	mVelX=0;
	mVelY=0;

	mColliders.resize(11);

	mColliders[0].w=6; mColliders[0].h=1;
	mColliders[1].w=10; mColliders[1].h=1;
	mColliders[2].w=14; mColliders[2].h=1;
	mColliders[3].w=16; mColliders[2].h=2;
	mColliders[4].w=18; mColliders[4].h=2;

	mColliders[ 5 ].w = 20;
   mColliders[ 5 ].h = 6;

   mColliders[ 6 ].w = 18;
   mColliders[ 6 ].h = 2;

   mColliders[ 7 ].w = 16;
   mColliders[ 7 ].h = 2;

   mColliders[ 8 ].w = 14;
   mColliders[ 8 ].h = 1;

   mColliders[ 9 ].w = 10;
   mColliders[ 9 ].h = 1;

   mColliders[ 10 ].w = 6;
   mColliders[ 10 ].h = 1;

	shiftColliders();
}

void Dot::handleEvent(SDL_Event& e){
	if (e.type==SDL_KEYDOWN && e.key.repeat==0){
		switch (e.key.keysym.sym){
			case SDLK_UP: mVelY -= DOT_VEL; break;
         case SDLK_DOWN: mVelY += DOT_VEL; break;
         case SDLK_LEFT: mVelX -= DOT_VEL; break;
         case SDLK_RIGHT: mVelX += DOT_VEL; break;
		}
	}
	else if (e.type==SDL_KEYUP && e.key.repeat==0){
		switch (e.key.keysym.sym){
         case SDLK_UP: mVelY += DOT_VEL; break;
         case SDLK_DOWN: mVelY -= DOT_VEL; break;
         case SDLK_LEFT: mVelX += DOT_VEL; break;
         case SDLK_RIGHT: mVelX -= DOT_VEL; break;
      }
   }
}

int checkCollision(std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b){
   int leftA, leftB;
   int rightA, rightB;
   int topA, topB;
   int bottomA, bottomB;

   for (int Abox=0;Abox<a.size();++Abox){
      leftA   = a[Abox].x;
      rightA  = a[Abox].x+a[Abox].w;
      topA    = a[Abox].y;
      bottomA = a[Abox].y+a[Abox].h;

      for (int Bbox=0;Bbox<b.size();++Bbox){
         leftB   = b[Bbox].x;
         rightB  = b[Bbox].x+b[Bbox].w;
         topB    = b[Bbox].y;
         bottomB = b[Bbox].y+b[Bbox].h;
			
			if( ( ( bottomA <= topB ) || ( topA >= bottomB ) || ( rightA <= leftB ) || ( leftA >= rightB ) ) == false )
				return true;
		}
   }

   return 0;
}

void Dot::move(std::vector<SDL_Rect>& otherColliders){
	int displace;

	mPosX += mVelX;
	shiftColliders();

	displace=checkCollision(mColliders,otherColliders);

	if (mPosX<0 || mPosX+DOT_WIDTH>SCREEN_WIDTH || displace){
		mPosX -= mVelX; //displace;
		shiftColliders();
	}

	mPosY += mVelY;
   shiftColliders();

	displace=checkCollision(mColliders,otherColliders);

   if (mPosY<0 || mPosY+DOT_HEIGHT>SCREEN_HEIGHT || displace){
      mPosY -= mVelY;
      shiftColliders();
	}
}

void Dot::render(){
	gDotTexture.render(mPosX,mPosY);
}

void Dot::shiftColliders(){
	int r=0;
	for (int set=0;set<mColliders.size();set++){
		mColliders[set].x=mPosX+(DOT_WIDTH-mColliders[set].w)/2;
		mColliders[set].y=mPosY+r;
		r += mColliders[set].h;
	}
}

std::vector<SDL_Rect>& Dot::getColliders(){
	return mColliders;
}

bool init(){
	if (SDL_Init(SDL_INIT_VIDEO)<0){
		std::cout << SDL_GetError() << std::endl;
		return false;
	}

	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1"))
		std::cout << "Linear Texture Filter Disabled" << std::endl;

	gWindow=SDL_CreateWindow("SDL Tutorial",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow==NULL){
      std::cout << SDL_GetError() << std::endl;
      return false;
   }

	gRenderer= SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (gRenderer==NULL){
      std::cout << SDL_GetError() << std::endl;
      return false;
   }
	SDL_SetRenderDrawColor(gRenderer,0xFF,0xFF,0xFF,0xFF);
	
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)){
      std::cout << SDL_GetError() << std::endl;
      return false;
   }

	return true;
}

bool loadMedia(){
	if (!gDotTexture.loadFromFile("dot.bmp")){
      std::cout << SDL_GetError() << std::endl;
      return false;
   }

	return true;
}

void close(){
	gDotTexture.free();
	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow=NULL;
	gRenderer=NULL;

	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char** argv){
	if (!init()){
		std::cout << "Failed to Initialize" << std::endl;
		return -1;
	}

	if (!loadMedia()){
		std::cout << "Failed to Load Media" << std::endl;
   	return -1;
	}
	
	bool quit=false;
	SDL_Event e;
	Dot dot(0,0), otherDot(SCREEN_WIDTH/4, SCREEN_HEIGHT/4);
	
	while (!quit){
		while (SDL_PollEvent(&e) != 0){
			quit = (e.type==SDL_QUIT);
			dot.handleEvent(e);
		}
		dot.move(otherDot.getColliders());
		
		SDL_SetRenderDrawColor(gRenderer,0xFF,0xFF,0xFF,0xFF);
		SDL_RenderClear(gRenderer);

		dot.render();
		otherDot.render();

		SDL_RenderPresent(gRenderer);
	}

	close();

	return 1;
}
