#include "Player.h"
#include <vector>

int main(){
	Drawable dr;
	Player player;
	std::vector<Drawable> drVec;
	//drVec.push_back(player);
	drVec.push_back(dr);
	Player * playerPtr = (Player *)(&(drVec[0]));
	playerPtr->handleEvent();
}
