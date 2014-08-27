/**
TODO
	-- comment code properly
	-- create library/character libraries
	-- test some sort of update with more entitities
	-- AI (potential map)
	-- 3D motion :
		-> create camera + generate proper viewing volume/walls
		-> change the move function to move in z rather than y
		-> redo collision in this way
**/

#include "Level.h"
#include "BaseFunc.h"
#include "Camera.h"

#include <iostream>
#include <string>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

Population pop;
std::vector<Drawable> drawables;
JShader shader;
KeyboardHandler handler;
Camera cam;

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
	
	drawables = initLevel(shader, pop);

	glClearColor(0.2f, 0.2f, 0.2f, 1.f);
	
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
   glEnable(GL_MULTISAMPLE);
	
	return true;
}

int update(void * data){
	pop.update();

	return 1;
}

void move(){
	vec3 pCenter = pop.move();
	//printf("%lf\t%lf\t%lf\n",pCenter.x, pCenter.y, pCenter.z);
	cam.push(pCenter);
}

void closeShader(){
	glDeleteProgram(shader.getProgramID());
}

//Try and get SDL out of the picture
void handleEvent(SDL_Event& e){
	if (e.key.repeat == 0 && (e.type == SDL_KEYUP || e.type == SDL_KEYDOWN)){
      pop.handleKey(keyCode(e));
	}
	if (keyCode(e) == SDLK_RIGHT)
		cam.rightMult(glm::rotate(0.01f, vec3(0, 1, 0)));
	if (keyCode(e) == SDLK_LEFT)
		cam.rightMult(glm::rotate(-0.01f, vec3(0, 1, 0)));
	if (keyCode(e) == SDLK_UP)
		cam.rightMult(glm::rotate(-0.01f, vec3(1, 0, 0)));
	if (keyCode(e) == SDLK_DOWN)
		cam.rightMult(glm::rotate(0.01f, vec3(1, 0, 0)));
}

void render(){
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
	std::vector<Drawable>::iterator drIter;
	shader.bind();
   for (drIter = drawables.begin(); drIter != drawables.end(); drIter++){
      if (drIter->isVisible()){
			drIter->updateMV();
			glBindTexture(GL_TEXTURE_2D, drIter->getTex());
			mat4 MVP = cam.getProjMat() * drIter->getMVMat();
	      shader.updateMVP(glm::value_ptr(MVP));
         shader.updateColor(drIter->getColorPtr());
         glBindVertexArray(drIter->getVAO());
         glDrawElements(GL_TRIANGLE_STRIP, drIter->getNumElems(), GL_UNSIGNED_INT, NULL);
      }
   }
	shader.unbind();
}

int keyCode(SDL_Event& e){
   return (int)e.key.keysym.sym;
}
