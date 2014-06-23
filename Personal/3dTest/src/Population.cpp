#include "Population.h"

Population::Population(){
	obsVec.clear();
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

void Population::addObs(Obstacle obs){
	obsVec.push_back(obs);
}

void Population::clearObs(){
	obsVec.clear();
}

void Population::move(){
	player.move();
	std::vector<Obstacle>::iterator obsIt;
	for (obsIt=obsVec.begin(); obsIt!=obsVec.end(); obsIt++){
		if (player.collidesWith(*obsIt){
			
		}
	}
	if (player.collidesWith
	//now handle obstacles
	//then handle other entities
}

void Population::update(){
	player.update();
}

void Population::createCollisionBuffers(){
	int nObs = obsVec.size();
	std::vector<colBuf> cBufVec;
	cBufVec.resize(nObs);

	player.setColBufVec(cBufVec);

	//do later for many active ents
}

Player * Population::getPlayer(){
	return &player;
}

Entity * Population::lastObsAsEnt(){
	return (Entity *)&obsVec.back();
}
