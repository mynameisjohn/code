#include "Level.h"
#include <glm/gtx/transform.hpp> 

const vec3 wallMin(-10000, -60300, -2000);
const vec3 wallMax(17000, 600, -50020);

std::vector<Drawable> initLevel(JShader& shader, Population& pop){
	std::vector<Drawable> drawables;
	glm::mat4 MV;
	vec3 color;
	
	//Note the negative Z scale...never got around that	
	MV = glm::translate(vec3(0, 999, 2500)) *
		  glm::scale(vec3(400, 400, -400));
	color = vec3(0.2, 0.4f, 0.8f);
   drawables.push_back(initPlayer(MV, color, shader, pop));
	
	MV = glm::translate(vec3(1500, -600, -2500)) *
		  glm::scale(vec3(400, 400, -400));
	color = vec3(0.4f, 0.8f, 0.2f);
	drawables.push_back(initObstacle(MV,color,shader,pop));
 
	MV = glm::translate(vec3(500, -600, -2500)) *
		  glm::scale(vec3(400, 400, -400));
   drawables.push_back(initObstacle(MV, color, shader, pop));
	
	color=vec3(1.f, 1.f, 1.f);
	//floor...
	MV = glm::translate(glm::vec3(-1000, -600, -2000)) * 
		  glm::rotate((float)(M_PI/2.f), glm::vec3(1, 0, 0)) * 
		  glm::scale(glm::vec3(8000, -2000, -2));
   drawables.push_back(initWall(MV, color, shader, pop));
	
	//back wall
	MV = glm::translate(glm::vec3(-1000, -600, -4000)) * 
		  glm::scale(glm::vec3(8000, 2500, -2));
   drawables.push_back(initWall(MV, color, shader, pop));

	MV = glm::translate(glm::vec3(-1000, -600, -2000)) * 
		  glm::rotate((float)(M_PI/2.f), glm::vec3(0, 1, 0)) * 
		  glm::scale(glm::vec3(2000, 2500, -2));
   drawables.push_back(initWall(MV, color, shader, pop));

	MV = glm::translate(glm::vec3(7000, -600, -2000)) * 
		  glm::rotate((float)(M_PI/2.f), glm::vec3(0, 1, 0)) * 
		  glm::scale(glm::vec3(2000, 2500, -2));
   drawables.push_back(initWall(MV, color, shader, pop));

	return drawables;
}

Drawable initPlayer(glm::mat4 MV, vec3 color, JShader& shader, Population& pop){
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
	
	Player * playerPtr = pop.getPlayer();
	dr = initCube(MV, shader);
   playerPtr->setCol(c);
   dr.setEntity((Entity *)playerPtr);
   dr.setColor(color);

	return dr;
}

Drawable initObstacle(glm::mat4 MV, vec3 color, JShader& shader, Population& pop){
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
	
	dr = initCube(MV, shader);
	obs.setCol(c);
   dr.setEntity(pop.addObs(obs));
   dr.setColor(color);
	
	return dr;
}

Drawable initAe(glm::mat4 MV, vec3 color, JShader& shader, Population& pop){
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
	
	dr = initCube(MV, shader);
	aE.setCol(c);
   dr.setEntity(pop.addActiveEnt(aE));
   dr.setColor(color);
	
	return dr;
}

Drawable initWall(glm::mat4 MV, vec3 color, JShader& shader, Population& pop){
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
	
	dr = initQuad(MV, shader);
	obs.setCol(c);
   dr.setEntity(pop.addObs(obs));
   dr.setColor(color);
	
	return dr;
}
