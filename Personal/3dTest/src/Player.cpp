#include <SDL2/SDL.h>

#include "Player.h"

Player::Player() : ActiveEnt(){
	mDash = 1.5f;
}

Player::Player(Collider c) : ActiveEnt(c){
	//NYI
}

Player::~Player(){
	//NYI
}

void Player::update(){
	if (grounded)
		mVel.y=0.f;
	else
		mVel.y+=2.f;//gravity?
	getHandleInfo();
}

void Player::handleKey(int k){
	mHandler.handleKey(k);
}

void Player::getHandleInfo(){
// uncomment to prohibit mid-air movement
//	if (grounded){
	float dashSpeed = mSpeed.x*(mHandler.getKeyState(SDLK_LSHIFT) ? mDash : 1.f);
	bool jump = mHandler.getKeyState(SDLK_SPACE);

	mVel.x=0;
	if (mHandler.getKeyState(SDLK_a))
		mVel.x -= dashSpeed;
	if (mHandler.getKeyState(SDLK_d))
		mVel.x += dashSpeed;
	
	mVel.y += jump && grounded ? mSpeed.y : 0;
	
	mVel.z=0;
	if (mHandler.getKeyState(SDLK_w))
		mVel.z -= mSpeed.z;
	if (mHandler.getKeyState(SDLK_s))
		mVel.z += mSpeed.z;
//	}
}
