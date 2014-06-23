#include "Player.h"

#include <assert.h>

Player::Player() : ActiveEnt(){
	mHandler = NULL;
}

Player::Player(Collider c) : ActiveEnt(c){
	mHandler = NULL;
}

Player::~Player(){
	mHandler = NULL;
}

void Player::setKeyHandler(KeyboardHandler * handlePtr){
	mHandler = handlePtr;
}

void Player::update(){
	getHandleInfo();
}

void Player::move(){	
	mPos += mCollider.move(mVel);
}

void Player::getHandleInfo(){
	assert(mHandler != NULL);

   int dash = mHandler->getKeyState((int)SDLK_SPACE) ? 2 : 1;
   int speed = mSpeed * dash;

   if (mHandler->getKeyState((int)SDLK_w))
      mVel.y = -speed;
   else if (mHandler->getKeyState((int)SDLK_s))
      mVel.y = speed;
   else
      mVel.y = 0;

   if (mHandler->getKeyState((int)SDLK_a))
      mVel.x = -speed;
   else if (mHandler->getKeyState((int)SDLK_d))
      mVel.x = speed;
   else
      mVel.x = 0;
}
