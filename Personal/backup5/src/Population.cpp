#include "Population.h"
#include <stdio.h>

/*
TODO
	-- Create morea active entities
	-- Create a proper update method
	-- hurr durr i don't know something will come up
*/

Population::Population(){
	clearObs();
}

Population::~Population(){
	obsVec.clear();
}

void Population::setPlayer(Player p){
	player = p;
}

void Population::setKeyHandler(KeyboardHandler * handlePtr){
	player.setKeyHandler(handlePtr);
}

Entity * Population::addObs(Obstacle obs){
	if (obsIdx>=obsVec.size()){
		printf("Too many obstacles added\n");
		return NULL;
	}

	obsVec[obsIdx]=obs;
//	obsVec.push_back(obs);
//	return (Entity *)&obsVec.back();
	return &(obsVec[obsIdx++]);
}

void Population::clearObs(){
	obsVec.clear();
	obsIdx=0;
}

void Population::move(){
	std::vector<Obstacle>::iterator obsIt;

	//move with respect to (WRT) walls and obstacles	
	player.moveWRT_walls();
	for (obsIt=obsVec.begin(); obsIt!=obsVec.end(); obsIt++){
		player.moveWRT_ent(*obsIt);
		//player.moveWRT_ent(obsVec[0]);
	}
}

void Population::update(){
	player.update();
	printf("It's really %ld\n",(long)(&obsVec[0]));
}

void Population::initObs(int n){
	clearObs();
	obsVec.resize(n);
}

Player * Population::getPlayer(){
	return &player;
}

Entity * Population::lastObsAsEnt(){
	Obstacle * obsPtr = &obsVec.back();
	return (Entity *)obsPtr;
}
