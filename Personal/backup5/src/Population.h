#ifndef POPULATION_H
#define POPULATION_H

#include "Player.h"
#include "Obstacle.h"

class Population{
	public:
		Population();
		~Population();
		void setPlayer(Player p);
		void setKeyHandler(KeyboardHandler *);
		void clearObs();
		void update();
		void move();
		void initObs(int);
		Player * getPlayer();
		Entity * addObs(Obstacle obs);
		Entity * lastObsAsEnt();
	private:
		Player player;
		std::vector<Obstacle> obsVec;
		int obsIdx;
};

#endif
