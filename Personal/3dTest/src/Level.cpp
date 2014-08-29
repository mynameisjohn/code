#include "Level.h"
#include <glm/gtx/transform.hpp> 

const vec3 wallMin(-1000, -600, -2000);
const vec3 wallMax(7000, 600, -4000);

std::unique_ptr<Population> initLevel(JShader& shader){
	std::unique_ptr<Population> pop(new Population());
	
	glm::mat4 MV;
	vec3 color;
	
	//Note the negative Z scale...never got around that	
	MV = glm::translate(vec3(0, 999, 2500)) *
		  glm::scale(vec3(400, 400, -400));
	color = vec3(0.2, 0.4f, 0.8f);
	initPlayer(MV, color, shader, pop->getPlayer());
	
	MV = glm::translate(vec3(1500, -600, -2500)) *
		  glm::scale(vec3(400, 400, -400));
	color = vec3(0.4f, 0.8f, 0.2f);
	pop->addObs(initObstacle(MV, color, shader));
 
	MV = glm::translate(vec3(500, -600, -2500)) *
		  glm::scale(vec3(400, 400, -400));
	pop->addObs(initObstacle(MV, color, shader));
	
	MV = glm::translate(vec3(1000, -600, -3500)) *
		  glm::scale(vec3(400, 400, -400));
	color = vec3(0.8f, 0.4f, 0.2f);
	pop->addActiveEnt(initAe(MV, color, shader));
	
	color=vec3(1.f, 1.f, 1.f);
	
	//floor...
	MV = glm::translate(glm::vec3(-1000, -600, -2000)) * 
		  glm::rotate((float)(M_PI/2.f), glm::vec3(1, 0, 0)) * 
		  glm::scale(glm::vec3(8000, -2000, -2));
	pop->addObs(initObstacle(MV, color, shader));
	
	//back wall
	MV = glm::translate(glm::vec3(-1000, -600, -4000)) * 
		  glm::scale(glm::vec3(8000, 2500, -2));
	pop->addObs(initObstacle(MV, color, shader));

	MV = glm::translate(glm::vec3(-1000, -600, -2000)) * 
		  glm::rotate((float)(M_PI/2.f), glm::vec3(0, 1, 0)) * 
		  glm::scale(glm::vec3(2000, 2500, -2));
	pop->addObs(initObstacle(MV, color, shader));

	MV = glm::translate(glm::vec3(7000, -600, -2000)) * 
		  glm::rotate((float)(M_PI/2.f), glm::vec3(0, 1, 0)) * 
		  glm::scale(glm::vec3(2000, 2500, -2));
	pop->addObs(initObstacle(MV, color, shader));

	return pop;
}

void initPlayer(glm::mat4 MV, vec3 color, JShader& shader, Player * playerPtr){
	Drawable dr;
	BoundBox bb;
	Collider c;
	iRect rect;

	vec3 translate = vec3(MV * glm::vec4(0, 0, 0, 1));
	vec3 scale = glm::abs(vec3(MV * glm::vec4(1, 1, 1, 1)) - translate);

   rect = iRect(0, 0, 40, 20);
	bb = BoundBox(translate, scale);
   c=Collider(wallMin, wallMax, bb);
   c.addSub(rect);
   rect = iRect(0, 20, 40, 20);
   c.addSub(rect);
   playerPtr->setCol(c);
	
	dr = initCube(MV, shader);
   dr.setColor(color);
	playerPtr->addDrawable(dr);

	return;
}

Obstacle initObstacle(glm::mat4 MV, vec3 color, JShader& shader){
	Obstacle obs;
	Drawable dr;
	BoundBox bb;
	Collider c;
	iRect rect;

	vec3 translate = vec3(MV * glm::vec4(0, 0, 0, 1));
	vec3 scale = glm::abs(vec3(MV * glm::vec4(1, 1, 1, 1)) - translate);

   rect = iRect(0, 0, 40, 20);
	bb = BoundBox(translate, scale);
   c=Collider(wallMin, wallMax, bb);
   c.addSub(rect);
   rect = iRect(0, 20, 40, 20);
   c.addSub(rect);
	obs.setCol(c);
	
	dr = initCube(MV, shader);
   dr.setColor(color);
	obs.addDrawable(dr);
	
	return obs;
}

ActiveEnt initAe(glm::mat4 MV, vec3 color, JShader& shader){
   ActiveEnt aE;
	Drawable dr;
	BoundBox bb;
	Collider c;
	iRect rect;

	vec3 translate = vec3(MV * glm::vec4(0, 0, 0, 1));
	vec3 scale = glm::abs(vec3(MV * glm::vec4(1, 1, 1, 1)) - translate);

   rect = iRect(0, 0, 40, 20);
	bb = BoundBox(translate, scale);
   c=Collider(wallMin, wallMax, bb);
   c.addSub(rect);
   rect = iRect(0, 20, 40, 20);
   c.addSub(rect);
	aE.setCol(c);
	
	dr = initCube(MV, shader);
   dr.setColor(color);
	aE.addDrawable(dr);
	
	return aE;
}

Obstacle initWall(glm::mat4 MV, vec3 color, JShader& shader){
	Obstacle obs;
	Drawable dr;
	BoundBox bb;
	Collider c;
	iRect rect;

	vec3 translate = vec3(MV * glm::vec4(0, 0, 0, 1));
	vec3 scale = glm::abs(vec3(MV * glm::vec4(1, 1, 1, 1)) - translate);

   rect = iRect(0, 0, 40, 20);
	bb = BoundBox(translate, scale);
   c=Collider(wallMin, wallMax, bb);
   c.addSub(rect);
   rect = iRect(0, 20, 40, 20);
   c.addSub(rect);
	obs.setCol(c);
	
	dr = initQuad(MV, shader);
   dr.setColor(color);
	obs.addDrawable(dr);
	
	return obs;
}
