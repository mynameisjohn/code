#include "Player.h"

void Player::handleEvent(SDL_Event& e){
   if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
      switch(e.key.keysym.sym){
         case SDLK_UP: mVelY -= speed; break;
         case SDLK_DOWN: mVelY += speed; break;
         case SDLK_LEFT: mVelX -= speed; break;
         case SDLK_RIGHT: mVelX += speed; break;
      }
   }
   else if ( e.type == SDL_KEYUP && e.key.repeat == 0 ){
      switch(e.key.keysym.sym){
         case SDLK_UP: mVelY += speed; break;
         case SDLK_DOWN: mVelY -= speed; break;
         case SDLK_LEFT: mVelX += speed; break;
         case SDLK_RIGHT: mVelX -= speed; break;
      }
   }	
}
