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
		void addObs(Obstacle obs);
		void clearObs();
		void update();
		void move();
		void createCollisionBuffers();
		Player * getPlayer();
		Entity * lastObsAsEnt();
	private:
		Player player;
		std::vector<Obstacle> obsVec;
};

#endif
