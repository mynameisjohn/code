#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <stdio.h>
#include <string>
#include <fstream>
#include <exception>
#include "BaseFunc.h"
#define VERT_SHADER "shaders/simpleVert.glsl"
#define FRAG_SHADER "shaders/simpleFrag.glsl"

#define SPACE_WIDTH 400
#define SPACE_HEIGHT 300

//JShader shader;
//Drawable square;

shadeCollective SC;
Player * playerPtr;

bool initGL(){
	//JShader shader;
	//Drawable square;

	Player player;
	Drawable square;
	//SC.dr.push_back(player);
	//SC.dr.push_back(square);
	//playerPtr = (Player *)(&(SC.dr[0]));
	

	//Load Vertex/Fragment Shader files
   if (!SC.shader.loadVert(VERT_SHADER) ||
       !SC.shader.loadFrag(FRAG_SHADER))
      return false;

   //Generate Shader Program
   if (!SC.shader.loadProgram())
      return false;

   SC.shader.bind();
	//Set Projection Matrix
	glm::mat4 proj = glm::ortho<GLfloat>(0.0,SPACE_WIDTH, SPACE_HEIGHT, 0.0, 1.0, -1.0);
	SC.shader.updateProj(glm::value_ptr(proj));
	
	if (!initGeom((Drawable *)(&(player)), "geom/square.geom",50, SPACE_HEIGHT/2)){
		printf("Error initializing geometry.\n");
		SC.shader.unbind();
		return false;
	}

	player.setColor(1.f, 0.f, 0.1f);
	
	if (!initGeom(&(square), "geom/rect.geom",SPACE_WIDTH/2, SPACE_HEIGHT/2)){
      printf("Error initializing geometry.\n");
      SC.shader.unbind();
      return false;
   }

	square.setColor(1.f, 0.5f, 0.f);

	//Set MV Matrix
	//SC.shader.updateMV(SC.dr[0].getMVPtr());
	//SC.shader.updateColor(SC.dr[0].getColorPtr());
	SC.shader.unbind();

	SC.dr.push_back(player);
	SC.dr.push_back(square);

	playerPtr = (Player *)(&(SC.dr[0]));

	//SC.shader = shader;
	//SC.dr.push_back(square);

	glClearColor(0.f, 0.f, 0.f, 1.f);

	return true;
}

bool initGeom(Drawable * dr, std::string src, int x, int y){
	std::ifstream in;
	in.open(src.c_str());
	if (!in.good()){
		printf("Invalid geometry file.\n");
		return false;
	}

	//surround this with try/catch
	try{
		std::string str;
		std::getline(in, str);
		int nVert = std::stoi(str);
		GLfloat vertices [nVert * 2];

		for (int i=0; i<nVert; i++){
			std::getline(in, str, ' ');
			vertices[i*2]=(GLfloat)std::stof(str)+(float)x;
			std::getline(in, str, ' ');
			vertices[i*2+1]=(GLfloat)std::stof(str)+(float)y;
		}

		GLuint indices [nVert];

		for (int i=0; i<nVert; i++){
			std::getline(in, str, ' ');
			indices[i]=(GLuint)std::stoi(str);
		}

		GLuint tmpVBO, tmpIBO;

		//Create VBO
		glGenBuffers( 1, &tmpVBO );
		glBindBuffer( GL_ARRAY_BUFFER, tmpVBO );
		glBufferData( GL_ARRAY_BUFFER, 2 * nVert * sizeof(GLfloat), vertices, GL_STATIC_DRAW );

		//Create IBO
		glGenBuffers( 1, &tmpIBO );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, tmpIBO );
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, nVert * sizeof(GLuint), indices, GL_STATIC_DRAW );

		dr->setVBO(tmpVBO);
		dr->setIBO(tmpIBO);

		std::getline(in, str);
		std::getline(in, str);

		int nSubCol = std::stoi(str);

		SDL_Rect top;
		std::getline(in, str, ' ');
		top.x=std::stoi(str)+x;

		std::getline(in, str, ' ');
		top.y=std::stoi(str)+y;

		std::getline(in, str, ' ');
		top.w=std::stoi(str);

		std::getline(in, str, ' ');
		top.h=std::stoi(str);

		dr->setTop(top);

		for (int i=0; i<nSubCol; i++){
			SDL_Rect tmp;
			std::getline(in, str, ' ');
			tmp.x=std::stoi(str)+x;

			std::getline(in, str, ' ');
			tmp.y=std::stoi(str)+y;

			std::getline(in, str, ' ');
			tmp.w=std::stoi(str);

			std::getline(in, str, ' ');
			tmp.h=std::stoi(str);

			dr->addSub(tmp);
		}
	}
	catch (std::ifstream::failure e){
		printf("Syntax Error in geometry file.\n");
		return false;
	}

   return true;
}
void update(){
	//handleCollisions();
	move();
}

void handleEvent(SDL_Event& e){
	playerPtr->handleEvent(e);
}
void move(){
	/*std::vector<Drawable>::iterator drIter;
   for (drIter = SC.dr.begin(); drIter != SC.dr.end(); drIter++)
			drIter->move(0, 0, SPACE_WIDTH, SPACE_HEIGHT);*/
	SC.dr[0].move(0, 0, SPACE_WIDTH, SPACE_HEIGHT,SC.dr[1].getTopColPtr());
}

void render(){
	glClear(GL_COLOR_BUFFER_BIT);

	std::vector<Drawable>::iterator drIter;
   for (drIter = SC.dr.begin(); drIter != SC.dr.end(); drIter++){
		if (drIter->drawMe()){
			SC.shader.bind();
			SC.shader.updateMV(drIter->getMVPtr());
			//drIter->setColor(0.5f,1.f,.2f);
			SC.shader.updateColor(drIter->getColorPtr());

			glEnableVertexAttribArray(SC.shader.getPosHandle());
			glBindBuffer(GL_ARRAY_BUFFER, drIter->getVBO());
			glVertexAttribPointer(SC.shader.getPosHandle(), 2, GL_FLOAT, GL_FALSE, 
										 2*sizeof(GL_FLOAT), NULL);
			
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, drIter->getIBO());
			glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);
			glDisableVertexAttribArray(SC.shader.getPosHandle());
			SC.shader.unbind();
		}
	}
}

void closeShader(){
	glDeleteProgram(SC.shader.getProgramID());
}

void showColliders(SDL_Renderer * renderer){
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x88);
	//std::vector<Drawable>::iterator drIter;
	//for (drIter = SC.dr.begin(); drIter != SC.dr.end(); drIter++){
		//SDL_RenderFillRect(renderer,drIter->getTopColPtr());
	//}
	SDL_Rect rect = {-20, -20, 20, 20};
	SDL_RenderFillRect(renderer, &rect);
	SDL_RenderPresent(renderer);
}
