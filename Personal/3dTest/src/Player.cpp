#include "Player.h"
#include <stdio.h>

void Player::handleEvent(SDL_Event& e){
   if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
      switch(e.key.keysym.sym){
         case SDLK_w: mVelY -= mSpeed; break;
         case SDLK_s: mVelY += mSpeed; break;
         case SDLK_a: mVelX -= mSpeed; break;
         case SDLK_d: mVelX += mSpeed; break;
      }
   }
   else if ( e.type == SDL_KEYUP && e.key.repeat == 0 ){
      switch(e.key.keysym.sym){
         case SDLK_w: mVelY += mSpeed; break;
         case SDLK_s: mVelY -= mSpeed; break;
         case SDLK_a: mVelX += mSpeed; break;
         case SDLK_d: mVelX -= mSpeed; break;
      }
   }
	/*
	else if (e.key.keysym.sym == SDLK_UP)
		printf("Speed is now: %d\n", mSpeed++);
	else if (e.key.keysym.sym == SDLK_DOWN)
      printf("Speed is now: %d\n", mSpeed--);
	*/	
}
