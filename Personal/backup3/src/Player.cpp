#include "Player.h"
#include <stdio.h>
#include "KeyboardHandler.h"

void Player::handleEvent(KeyboardHandler * handler){

	int dash = handler->getKeyState((int)SDLK_SPACE) ? 2 : 1;
	int speed = mSpeed * dash;

	if (handler->getKeyState((int)SDLK_w))
		mVelY = -speed;
   else if (handler->getKeyState((int)SDLK_s))
      mVelY = speed;
	else
		mVelY = 0;

	if (handler->getKeyState((int)SDLK_a))
      mVelX = -speed;
   else if (handler->getKeyState((int)SDLK_d))
      mVelX = speed;
   else
      mVelX = 0;



/*
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
*/
}
/*
bool Player::collidesWith(std::vector<Entity>::iterator eIt){
   if ((mCollider.collidesWith(eIt->getCollider()))){ //mCollider))){//only tops for now
      eIt->step();//steppedOn = true;
      return true;
   }
   else{
      eIt->step();//steppedOn = false;
      return false;
   }
}
*/
