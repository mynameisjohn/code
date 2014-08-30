#include <SDL2/SDL.h>

#include "Player.h"
#include <glm/gtx/transform.hpp>

Player::Player() : ActiveEnt(){
	mDash = 1.5f;
	th=0.f;
}

Player::Player(Collider c) : ActiveEnt(c){
	//NYI
}

Player::~Player(){
	//NYI
}

void Player::update(){
	vec3 x,y;
	x = center() + vec3(320.f*cos(th), 0.f, 320.f*sin(th));
	th+=0.1f;
	y = center() + vec3(320.f*cos(th), 0.f, 320.f*sin(th));
	mDrawables[1].leftMultMV(glm::translate(y-x));

	if (mCollider.isGrounded())
		mVel.y=0.f;
	else
		mVel.y-=2.f;//gravity?
	getHandleInfo();
}

void Player::handleKey(int k){
	mHandler.handleKey(k);
}

void Player::getHandleInfo(){
// uncomment to prohibit mid-air movement
//	if (mCollider.isGrounded){
	float dashSpeed = mSpeed.x*(mHandler.getKeyState(SDLK_LSHIFT) ? mDash : 1.f);
	bool jump = mHandler.getKeyState(SDLK_SPACE);

	mVel.x=0;
	if (mHandler.getKeyState(SDLK_a))
		mVel.x -= dashSpeed;
	if (mHandler.getKeyState(SDLK_d))
		mVel.x += dashSpeed;
	
	mVel.y += jump && mCollider.isGrounded() ? mSpeed.y : 0;
	
	mVel.z=0;
	if (mHandler.getKeyState(SDLK_w))
		mVel.z -= mSpeed.z;
	if (mHandler.getKeyState(SDLK_s))
		mVel.z += mSpeed.z;
//	}
}
