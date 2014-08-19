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

#include <iostream>
#include <string>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

Population pop;
std::vector<Drawable> drawables;
JShader shader;
KeyboardHandler handler;

const int SPACE_WIDTH = 400;
const int SPACE_HEIGHT = 300;
const int SPACE_DEPTH = 200;

void printMat(glm::mat4 mat){
	for (int i=0;i<4;i++){
		std::cout << "[ ";
		for (int j=0;j<4;j++){
			std::cout << mat[i][j] << ", ";
		}
		std::cout << "]" << std::endl;
	}
}

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
   glm::mat4 ortho = glm::ortho<GLfloat>(0.f, 400.f, 300.f, 0.f, 0.f, 100.f);
	glm::mat4 persp = glm::perspective<GLfloat>(M_PI*.95f, 4.f/3.f, 25.f, 1000.f);
	persp = glm::scale(glm::vec3(1.f, -1.f, -1.f)) * persp;

	shader.updateProj(glm::value_ptr(persp));

	drawables = initLevel(shader, pop);

	glClearColor(0.2f, 0.2f, 0.2f, 1.f);
	
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);
   
	return true;
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
      pop.handleKey((int)e.key.keysym.sym);
}

void render(){
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
