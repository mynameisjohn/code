#include "Level.h"
#include <glm/gtx/transform.hpp> 

const vec3 wallMin(-1000, -600, -2000);
const vec3 wallMax(7000, 600, -4000);

std::vector<Drawable> initLevel(JShader& shader, Population& pop){
	std::vector<Drawable> drawables;
	glm::mat4 MV;
	vec3 color;
/*
	glEnableVertexAttribArray(shader.getPosHandle());
	glVertexAttribPointer(shader.getPosHandle(), 4, GL_FLOAT, 0, 0, 0);
	glEnableVertexAttribArray(shader.getTexCoordHandle());
	glVertexAttribPointer(shader.getTexCoordHandle(), 2, GL_FLOAT, 0, 0, 0);
*/
	//Note the negative Z scale...never got around that	
	MV = glm::translate(vec3(0, 999, 3500)) *
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
	
	//bug with back wall...
	MV = glm::translate(glm::vec3(-1000, -600, -2000)) * 
		  glm::rotate((float)(M_PI/2.f), glm::vec3(1, 0, 0)) * 
		  glm::scale(glm::vec3(8000, -2000, 1));
	color=vec3(1.f, 1.f, 1.f);
   drawables.push_back(initAe(MV, color, shader, pop));
	
	MV = glm::translate(glm::vec3(-1000, -600, -4000)) * 
		  glm::scale(glm::vec3(8000, 2500, 1));
   drawables.push_back(initAe(MV, color, shader, pop));
	
	return drawables;
}

Drawable initPlayer(glm::mat4 MV, vec3 color, JShader& shader, Population& pop){
	Drawable dr;
	BoundBox bb;
	Collider c;
	iRect rect;

	vec3 translate = vec3(MV * glm::vec4(0, 0, 0, 1));
	vec3 scale = vec3(MV * glm::vec4(1, 1, 1, 1)) - translate;
	scale.z *= -1.f;

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
	vec3 scale = vec3(MV * glm::vec4(1, 1, 1, 1)) - translate;
	scale.z *= -1.f;

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
	vec3 scale = vec3(MV * glm::vec4(1, 1, 1, 1)) - translate;
	scale.z *= -1.f;

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

std::pair<vec3, vec3> createWalls(){

}
