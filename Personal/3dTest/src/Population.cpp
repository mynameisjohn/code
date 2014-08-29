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

void Population::draw(int MVHandle, int ColorHandle){
	player.draw(MVHandle, ColorHandle);

	ObsPtrVec::iterator obsIt;
	AePtrVec::iterator aeIt;

	for (obsIt=obsVec.begin(); obsIt!=obsVec.end(); obsIt++)
		obsIt->get()->draw(MVHandle, ColorHandle);
	
	for (aeIt=aeVec.begin(); aeIt!=aeVec.end(); aeIt++)
		aeIt->get()->draw(MVHandle, ColorHandle);
}

void Population::setPlayer(Player p){
	player = p;
}

//These two vectors are held by smart pointers so I can polymorphize
void Population::addObs(Obstacle obs){//default copy constructor???
	obsVec.push_back(std::unique_ptr<Obstacle>(new Obstacle(obs)));
}

void Population::addActiveEnt(ActiveEnt aE){
	aeVec.push_back(std::unique_ptr<ActiveEnt>(new ActiveEnt(aE)));
}

void Population::handleKey(int k){
	player.handleKey(k);
}

glm::vec4 Population::move(){
	ObsPtrVec::iterator obsIt;
	AePtrVec::iterator aeIt;

	//move with respect to (WRT) walls and obstacles	
	player.moveWRT_walls();
	for (obsIt=obsVec.begin(); obsIt!=obsVec.end(); obsIt++){
		player.moveWRT_ent(*(*obsIt));
	}

	for (aeIt=aeVec.begin(); aeIt!=aeVec.end(); aeIt++){
		aeIt->get()->moveWRT_walls();
		for (obsIt=obsVec.begin(); obsIt!=obsVec.end(); obsIt++){
			aeIt->get()->moveWRT_ent(*(*obsIt));
		}
	}
	

	return glm::vec4(player.center(), fabs(player.getVel().x));
}

void Population::update(){
	ObsPtrVec::iterator obsIt;
	AePtrVec::iterator aeIt;

	player.update();
	
	for (aeIt=aeVec.begin(); aeIt!=aeVec.end(); aeIt++)
		aeIt->get()->update();
	//printf("It's really %ld\n",(long)(&obsVec[0]));
	for (obsIt=obsVec.begin(); obsIt!=obsVec.end(); obsIt++)
		obsIt->get()->update();
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
