#ifndef PLAYER_H
#define PLAYER_H

#include "ActiveEnt.h"
#include "KeyboardHandler.h"

class Player: public ActiveEnt{
	public:
		Player();
		Player(Collider c);
		~Player();
		void update();
		void getHandleInfo();
		void handleKey(int k);
	private:
		KeyboardHandler mHandler;
		float mDash, th;
};

#endif
