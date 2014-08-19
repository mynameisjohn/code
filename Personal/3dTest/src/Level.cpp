#include "Level.h"
#include <glm/gtx/transform.hpp> 

std::vector<Drawable> initLevel(JShader& shader, Population& pop){
	std::vector<Drawable> drawables;
	
	const int nObs = 2;
   const int nAe = 1;

   pop.initObs(nObs);
   pop.initAe(nAe);

	glm::mat4 MV = glm::translate(glm::vec3(-200, 2000, -300)) *
                  //glm::rotate((float)(M_PI/2.f), glm::vec3(1, 0, 0)) *
                  glm::scale(glm::vec3(1000, 1000, 1));

   drawables.push_back(initPlayer(MV, shader, pop));

   drawables.push_back(initObstacle(glm::vec3(0, 2000, 3300), shader, pop));
   drawables.push_back(initObstacle(glm::vec3(300, 40, 0), shader, pop));
	
	MV = glm::translate(glm::vec3(-2500, 2000, -450)) * 
						glm::rotate((float)(M_PI/2.f), glm::vec3(1, 0, 0)) * 
						glm::scale(glm::vec3(10000, 600, 1));

   drawables.push_back(initAe(MV, shader, pop));

	return drawables;
}

Drawable initPlayer(glm::mat4 MV, JShader& shader, Population& pop){
	Drawable dr;
	BoundBox bb;
	Collider c;
	iRect rect;

	glm::vec4 translate = MV * glm::vec4(0, 0, 0, 1);

	Player * playerPtr = pop.getPlayer();
	dr = initQuad(MV, shader);
	bb = BoundBox(0, 0, 0, 1000, 1000, 1000);
   c.setBB(bb);
   rect = iRect(0, 0, 40, 20);
   c.addSub(rect);
   rect = iRect(0, 20, 40, 20);
   c.addSub(rect);
   playerPtr->setCol(c);
   playerPtr->translate(translate.x, translate.y, translate.z);
   //playerPtr->setKeyHandler(&handler);
   dr.setEntity((Entity *)playerPtr);
   dr.setColor(0.871, 0.871, 0.871);

	return dr;
}

Drawable initObstacle(glm::vec3 translate, JShader& shader, Population& pop){
	Drawable dr;
   BoundBox bb;
   Collider c;
   iRect rect;

	Obstacle obs;

	dr = initQuad(glm::scale(glm::vec3(500, 500, 1)), shader);
   c = Collider();
   c.setWalls(0, 0, 0, 400, 300, 300);
   bb = BoundBox(0, 0, 0, 40, 40, 40);
   c.setBB(bb);
   rect = iRect(0, 0, 40, 20);
   c.addSub(rect);
   rect = iRect(0, 20, 40, 20);
   c.addSub(rect);
   obs.setCol(c);
   obs.translate(translate);
   dr.setEntity(pop.addObs(obs)); //lastObsAsEnt());
   dr.setColor(0.8f, 0.4f, 0.2f);

	return dr;
}

Drawable initAe(glm::mat4 MV, JShader& shader, Population& pop){
   Drawable dr;
   BoundBox bb;
   Collider c;
   iRect rect;
	glm::vec4 translate = MV * glm::vec4(0, 0, 0, 1);
   ActiveEnt aE;

   dr = initQuad(MV, shader);
   c = Collider();
   c.setWalls(0, 0, 0, 400, 300, 300);
   bb = BoundBox(0, 0, 0, 40, 40, 40);
   c.setBB(bb);
   rect = iRect(0, 0, 40, 20);
   c.addSub(rect);
   rect = iRect(0, 20, 40, 20);
   c.addSub(rect);
   aE.setCol(c);
   aE.translate(translate.x, translate.y, translate.z);
   dr.setEntity(pop.addActiveEnt(aE));
   dr.setColor(0.4f, 0.8f, 0.2f);

   return dr;
}

