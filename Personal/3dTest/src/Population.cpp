#include "Population.h"
#include <stdio.h>

/*
TODO
	-- Create morea active entities
	-- Create a proper update method
	-- hurr durr i don't know something will come up
*/

Population::Population(){
	//NYI
}

Population::~Population(){
	//NYI
}

void Population::setPlayer(Player p){
	player = p;
}

//These two vectors are held by smart pointers so I can polymorphize
Entity * Population::addObs(Obstacle obs){//default copy constructor???
	obsVec.push_back(std::unique_ptr<Obstacle>(new Obstacle(obs)));
	
	return obsVec.back().get();
}

Entity * Population::addActiveEnt(ActiveEnt aE){
	aeVec.push_back(std::unique_ptr<ActiveEnt>(new ActiveEnt(aE)));

	return aeVec.back().get();
}

void Population::handleKey(int k){
	player.handleKey(k);
}

vec3 Population::move(){
	ObsPtrVec::iterator obsIt;

	//move with respect to (WRT) walls and obstacles	
	player.moveWRT_walls();
	for (obsIt=obsVec.begin(); obsIt!=obsVec.end(); obsIt++){
		player.moveWRT_ent(*(*obsIt));
	}

	return player.center();
}

void Population::update(){
	player.update();
	//printf("It's really %ld\n",(long)(&obsVec[0]));
}
/*
void Population::initObs(int n){
	clearObs();
	obsVec.resize(n);
}

void Population::initAe(int n){
	clearAe();
	aeVec.resize(n);
}
*/

Player * Population::getPlayer(){
	return &player;
}
