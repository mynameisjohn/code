#ifndef POPULATION_H
#define POPULATION_H

#include "Player.h"
#include "Obstacle.h"
#include <memory>

typedef std::vector<std::unique_ptr<Obstacle> > ObsPtrVec;
typedef std::vector<std::unique_ptr<ActiveEnt> > AePtrVec;

class Population{
	public:
		Population();
		~Population();
		void setPlayer(Player p);
		void handleKey(int k);
		//void clearObs();
		//void clearAe();
		void update();
		vec3 move();
		//void initObs(int);
		//void initAe(int);
		Player * getPlayer();
		Entity * addObs(Obstacle obs);
		Entity * addActiveEnt(ActiveEnt aE);
	private:
		Player player;
		ObsPtrVec obsVec;
		AePtrVec aeVec;
		//int obsIdx, aeIdx;
	public:
		inline vec3 getPlayerCenter(){
			return player.center();
		}
};

#endif
