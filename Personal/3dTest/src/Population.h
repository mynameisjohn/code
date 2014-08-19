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
		void handleKey(int k);
		void clearObs();
		void clearAe();
		void update();
		void move();
		void initObs(int);
		void initAe(int);
		Player * getPlayer();
		Entity * addObs(Obstacle obs);
		Entity * addActiveEnt(ActiveEnt aE);
	private:
		Player player;
		std::vector<Obstacle> obsVec;
		std::vector<ActiveEnt> aeVec;
		int obsIdx, aeIdx;
};

#endif
