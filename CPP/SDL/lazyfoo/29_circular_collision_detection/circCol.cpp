#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

typedef struct Circle{
	int x, y, r;
} Circle;

int distSq(int x1, int y1, int x2, int y2){
	int dX = x2-x1;
	int dY = y2-y1;
	return dX*dX+dY*dY;
}

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
      void move(SDL_Rect& square,Circle& circle);
      void render();
		Circle& getCollider();
   private:
      int mPosX, mPosY;
      int mVelX, mVelY;
		Circle mCollider;
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

	mCollider.r = DOT_WIDTH/2;

	shiftColliders();
}

Circle& Dot::getCollider(){
	return mCollider;
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

bool checkCollision(Circle& a, Circle& b){
	int rSq=a.r+b.r;
	rSq*=rSq;

	int diff=distSq(a.x,a.y,b.x,b.y)-rSq;

	if (distSq(a.x,a.y,b.x,b.y)<rSq)
		return true;

	return false;
}

int checkCollision(SDL_Rect& a, SDL_Rect& b){
	//we are checking to see if a is going to collide with b
	const int FROM_LEFT=0x1, FROM_RIGHT=0x2, FROM_TOP=0x4, FROM_BOTTOM=0x8;
}

bool checkCollision(Circle& a, SDL_Rect& b){
	int dX, dY;

	if (a.x<b.x)
		dX=b.x;
	else if (a.x>b.x+b.w)
		dX=b.x+b.w;
	else
		dX=a.x;

	if (a.y<b.y)
		dY=b.y;
	else if (a.y>b.y+b.h)
		dY=b.y+b.h;
	else
		dY=a.y;

	if (distSq(a.x,a.y,dX,dY)<a.r*a.r)
		return true;

	return false;
}

void Dot::move(SDL_Rect& square, Circle& circle){
	mPosX += mVelX;
	shiftColliders();

	if (mPosX<0 || mPosX+DOT_WIDTH>SCREEN_WIDTH || checkCollision( mCollider, square ) || checkCollision( mCollider, circle )){
		mPosX -= mVelX;
		shiftColliders();
	}
	
	mPosY += mVelY;
   shiftColliders();

   if (mPosY<0 || mPosY+DOT_HEIGHT>SCREEN_HEIGHT || checkCollision( mCollider, square ) || checkCollision( mCollider, circle )){
      mPosY -= mVelY;
      shiftColliders();
	}
}

void Dot::render(){
	gDotTexture.render(mPosX-mCollider.r,mPosY-mCollider.r);
}

void Dot::shiftColliders(){
	mCollider.x=mPosX;
	mCollider.y=mPosY;
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
	Dot dot(Dot::DOT_WIDTH/2,Dot::DOT_HEIGHT/2), otherDot(SCREEN_WIDTH/4, SCREEN_HEIGHT/4);
	SDL_Rect wall;
	wall.x = 300;
	wall.y = 40;
	wall.w = 40;
	wall.h = 400;
	
	while (!quit){
		while (SDL_PollEvent(&e) != 0){
			quit = (e.type==SDL_QUIT);
			dot.handleEvent(e);
		}
		dot.move(wall,otherDot.getCollider());
		SDL_SetRenderDrawColor(gRenderer,0xFF,0xFF,0xFF,0xFF);
		SDL_RenderClear(gRenderer);
		//std::cout << dot.getCollider().x << ", " << dot.getCollider().y << std::endl;
		dot.render();
		otherDot.render();
		SDL_SetRenderDrawColor(gRenderer,0xFF,0x00,0x00,0xFF);
		SDL_RenderDrawRect(gRenderer,&wall);

		SDL_RenderPresent(gRenderer);
	}

	close();

	return 1;
}
