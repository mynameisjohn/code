#include "Player.h"

#include <assert.h>

Player::Player() : ActiveEnt(){
	mHandler = new KeyboardHandler;
}

Player::Player(Collider c) : ActiveEnt(c){
	mHandler = new KeyboardHandler;
}

Player::~Player(){
	delete mHandler;
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

void Player::handleKey(int k){
	mHandler->handleKey(k);
}

void Player::getHandleInfo(){
	assert(mHandler != NULL);

   int dash = mHandler->getKeyState((int)SDLK_SPACE) ? 2 : 1;
   int speed = dash * mSpeed;

   if (mHandler->getKeyState((int)SDLK_w))
      mVel.z = -speed/8;
   else if (mHandler->getKeyState((int)SDLK_s))
      mVel.z = speed/8;
   else
      mVel.z = 0;

   if (mHandler->getKeyState((int)SDLK_a))
      mVel.x = -speed;
   else if (mHandler->getKeyState((int)SDLK_d))
      mVel.x = speed;
   else
      mVel.x = 0;
}
