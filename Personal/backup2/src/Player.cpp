#include "Player.h"

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
}
