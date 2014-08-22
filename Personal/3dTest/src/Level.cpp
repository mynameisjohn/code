#include "Level.h"
#include <glm/gtx/transform.hpp> 

std::vector<Drawable> initLevel(JShader& shader, Population& pop){
	
	const int nObs = 2;
   const int nAe = 2;
	std::vector<Drawable> drawables;
	glm::mat4 MV;

   pop.initObs(nObs);
   pop.initAe(nAe);
	
	MV = glm::translate(vec3(0, -999, -500)) *
		  glm::rotate((float)(M_PI/6.f), glm::vec3(0, 1, 0)) * 
		  glm::scale(vec3(400, 400, 400));
   drawables.push_back(initPlayer(MV, shader, pop));

	MV = glm::translate(vec3(-500, 200, -500)) *
		  glm::scale(vec3(400, 400, 1));
	drawables.push_back(initObstacle(MV,shader,pop));
 
	MV = glm::translate(vec3(500, 200, -500)) *
		  glm::scale(vec3(400, 400, 1));
   drawables.push_back(initObstacle(MV, shader, pop));

	MV = glm::translate(glm::vec3(-1000, 600, -1200)) * 
		  glm::rotate((float)(M_PI/2.f), glm::vec3(1, 0, 0)) * 
		  glm::scale(glm::vec3(2000, 770, 1));
   drawables.push_back(initAe(MV, shader, pop));
	
	return drawables;
}

Drawable initPlayer(glm::mat4 MV, JShader& shader, Population& pop){
	Drawable dr;
	BoundBox bb;
	Collider c;
	iRect rect;

	vec3 translate = vec3(MV * glm::vec4(0, 0, 0, 1));

	Player * playerPtr = pop.getPlayer();
	dr = initCube(MV, shader);
	bb = BoundBox(translate, vec3(400, 400, 2));
   c.setBB(bb);
   rect = iRect(0, 0, 40, 20);
   c.addSub(rect);
   rect = iRect(0, 20, 40, 20);
   c.addSub(rect);
   playerPtr->setCol(c);
   dr.setEntity((Entity *)playerPtr);
   dr.setColor(0.871, 0.871, 0.871);

	return dr;
}

Drawable initObstacle(glm::mat4 MV, JShader& shader, Population& pop){
	Drawable dr;
   BoundBox bb;
   Collider c;
   iRect rect;

	Obstacle obs;

	vec3 translate = vec3(MV * glm::vec4(0, 0, 0, 1));

	dr = initQuad(MV, shader);
   c = Collider();
	bb = BoundBox(vec3(), vec3(400, 400, 1));
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
	vec3 translate = vec3(MV * glm::vec4(0, 0, 0, 1));
   ActiveEnt aE;

   dr = initQuad(MV, shader);
   c = Collider();
	bb = BoundBox(vec3(), vec3(400, 400, 1));
   c.setBB(bb);
   rect = iRect(0, 0, 40, 20);
   c.addSub(rect);
   rect = iRect(0, 20, 40, 20);
   c.addSub(rect);
   aE.setCol(c);
   aE.translate(translate);
   dr.setEntity(pop.addActiveEnt(aE));
   dr.setColor(0.4f, 0.8f, 0.2f);

   return dr;
}

std::pair<vec3, vec3> createWalls(){

}
