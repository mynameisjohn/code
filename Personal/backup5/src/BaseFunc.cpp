/**
TODO
	-- comment code properly
	-- create library/character libraries
	-- test some sort of update with more entitities
	-- AI (potential map)
	-- 3D motion (figure out perspective projection matrix)
**/

#include "JShader.h"
#include "BaseFunc.h"
#include "Population.h"

#include <string>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

Population pop;
std::vector<Drawable> drawables;
JShader shader;
KeyboardHandler handler;

bool initGL(){
	const std::string vertShaderSrc = "shaders/simpleVert.glsl";
	const std::string fragShaderSrc = "shaders/simpleFrag.glsl";

	//Load Vertex/Fragment Shader files
   if (!shader.loadVert(vertShaderSrc) ||
       !shader.loadFrag(fragShaderSrc))
      return false;

   //Generate Shader Program
   if (!shader.loadProgram())
      return false;

   //Set Projection Matrix
   shader.bind();
   glm::mat4 proj = glm::ortho<GLfloat>(0.0,400.f, 300.f, 0.0, 1.0, -1.0);
   shader.updateProj(glm::value_ptr(proj));

	initLevel();

	glClearColor(0.2f, 0.2f, 0.2f, 1.f);

   return true;
}

void initPlayer(){
	Drawable dr;
	BoundBox bb;
	Collider c;
	iRect rect;

	Player * playerPtr = pop.getPlayer();
	dr = initQuad();
	bb = BoundBox(0, 0, 0, 40, 40, 40);
   c.setBB(bb);
   rect = iRect(0, 0, 40, 20);
   c.addSub(rect);
   rect = iRect(0, 20, 40, 20);
   c.addSub(rect);
   playerPtr->setCol(c);
   playerPtr->translate(10, 20, 0);
   playerPtr->setKeyHandler(&handler);
   dr.setEntity((Entity *)playerPtr);
   dr.setColor(0.2f, 0.4f, 0.8f);
   drawables.push_back(dr);

	return;
}

void initObstacle(int x, int y){
	Drawable dr;
   BoundBox bb;
   Collider c;
   iRect rect;

	Obstacle obs;

	dr = initQuad();
   c = Collider();
   c.setWalls(0, 0, 0, 400, 300, 300);
   bb = BoundBox(0, 0, 0, 40, 40, 40);
   c.setBB(bb);
   rect = iRect(0, 0, 40, 20);
   c.addSub(rect);
   rect = iRect(0, 20, 40, 20);
   c.addSub(rect);
   obs.setCol(c);
   obs.translate(x, y, 0);
   dr.setEntity(pop.addObs(obs)); //lastObsAsEnt());
   dr.setColor(0.8f, 0.4f, 0.2f);
   drawables.push_back(dr);

	return;
}

//All of this will be moved to a separate library...in due time
bool initLevel(){
	int nObs = 2;
	
	pop.initObs(nObs);
	
	initPlayer();
	
	initObstacle(200, 200);
	initObstacle(300, 0);
	
	return true;
}

Drawable initQuad(){
   const int nVert=4, dim=2, nIndices=4;
   const int vStride = 4*2*sizeof(GLint);
   const int tStride = 4*2*sizeof(GLfloat);
   const int iStride = 4*sizeof(GLuint);

	Drawable dr;

   const GLint vertices[nVert][dim] = {
      {0, 0}, {40, 0},
      {0, 40}, {40, 40}
   };
   const GLfloat texCoords[nVert][dim] = {
      {0.f, 0.f}, {1.f, 0.f},
      {0.f, 1.f}, {1.f, 1.f}
   };
   const GLuint indices[4] = {0, 1, 2, 3};

   GLuint tmpVAO;
   glGenVertexArrays(1, &tmpVAO);
   glBindVertexArray(tmpVAO);

   GLuint buffers[3];
   glGenBuffers(3, buffers);

   //vertices
   glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
   glBufferData(GL_ARRAY_BUFFER, vStride, vertices, GL_STATIC_DRAW);
   glEnableVertexAttribArray(shader.getPosHandle());
   glVertexAttribPointer(shader.getPosHandle(), dim, GL_INT, 0, 0, 0);

   //tex coords
   glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
   glBufferData(GL_ARRAY_BUFFER, tStride, texCoords, GL_STATIC_DRAW);
   glEnableVertexAttribArray(shader.getTexCoordHandle());
   glVertexAttribPointer(shader.getTexCoordHandle(), dim, GL_FLOAT, 0, 0, 0);

   //indices
   glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, buffers[2] );
   glBufferData( GL_ELEMENT_ARRAY_BUFFER, iStride, indices, GL_STATIC_DRAW );

   glBindVertexArray(0);

	dr.setVAO(tmpVAO);

   return dr;
}

void update(){
	pop.update();
}

void move(){
	pop.move();
}

void closeShader(){
	glDeleteProgram(shader.getProgramID());
}

//Try and get SDL out of the picture
void handleEvent(SDL_Event& e){
	if (e.key.repeat == 0 && (e.type == SDL_KEYUP || e.type == SDL_KEYDOWN))
      handler.handleKey((int)e.key.keysym.sym);
}

void render(){
   glClear(GL_COLOR_BUFFER_BIT);

   std::vector<Drawable>::iterator drIter;
	shader.bind();
   for (drIter = drawables.begin(); drIter != drawables.end(); drIter++){
      drIter->updateMV();
      if (drIter->isVisible()){
         shader.updateMV(drIter->getMVPtr());
         shader.updateColor(drIter->getColorPtr());
         glBindVertexArray(drIter->getVAO());
         glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, NULL);
      }
   }
	shader.unbind();
}
