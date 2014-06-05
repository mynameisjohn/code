#include <string>
#include <fstream>
#include <exception>

#include "JShader.h"
#include "BaseFunc.h"
#include "Player.h"

#define SPACE_WIDTH 400
#define SPACE_HEIGHT 300

#define VERT_SHADER "shaders/simpleVert.glsl"
#define FRAG_SHADER "shaders/simpleFrag.glsl"

JShader shader;
std::vector<Drawable> drawables;
std::vector<Entity> entities;
Player * playerPtr;


bool initGL(){
	//Load Vertex/Fragment Shader files
   if (!shader.loadVert(VERT_SHADER) ||
       !shader.loadFrag(FRAG_SHADER))
      return false;

   //Generate Shader Program
   if (!shader.loadProgram())
      return false;

	//Set Projection Matrix
	shader.bind();
	glm::mat4 proj = glm::ortho<GLfloat>(0.0,
								SPACE_WIDTH, SPACE_HEIGHT, 0.0, 1.0, -1.0);
	shader.updateProj(glm::value_ptr(proj));
	shader.unbind();

	//For the purpose of this example, the drawables will be
	//	+ 1 Rectangle (passive)
	// + 2 Triangles (aggressive)
	// + 2 Square (player)

	Drawable rect_dr, tri1_dr, tri2_dr, square_dr;
	Entity tri1_e, tri2_e;
	Player square_e;
	
	rect_dr.setColor(1.f, 0.2f, 0.2f);
	tri1_dr.setColor(1.f, 0.3f, 0.f);
	tri2_dr.setColor(0.f, 0.5f, 0.8f);
	square_dr.setColor(0.1f, 0.3f, 0.7f);

	tri1_e.setWalls(0, 0, SPACE_WIDTH, SPACE_HEIGHT);
	tri2_e.setWalls(0, 0, SPACE_WIDTH, SPACE_HEIGHT);
	square_e.setWalls(0, 0, SPACE_WIDTH, SPACE_HEIGHT);

   drawables.push_back(rect_dr);   //This rect isn't an entity
   drawables.push_back(tri1_dr);   entities.push_back(tri1_e);
   drawables.push_back(tri2_dr);   entities.push_back(tri2_e);
   drawables.push_back(square_dr); entities.push_back(square_e);

	drawables[1].setEntity(&entities[0]);
	drawables[2].setEntity(&entities[1]);
	drawables[3].setEntity(&entities[2]);

	playerPtr = (Player *)(&entities.back());

   if (!initGeom(&drawables[3], "geom/square.geom", 3*SPACE_WIDTH/4, SPACE_HEIGHT/2)){
      printf("Error initializing geometry.\n");
      return false;
   }

   if (!initGeom(&drawables[2], "geom/square.geom", 50, SPACE_HEIGHT/2)){
      printf("Error initializing geometry.\n");
      return false;
   }

   if (!initGeom(&drawables[1], "geom/square.geom", 50, 50)){
      printf("Error initializing geometry.\n");
      return false;
   }

   if (!initGeom(&drawables[0], "geom/rect.geom", 250, SPACE_HEIGHT/2)){
      printf("Error initializing geometry.\n");
      return false;
   }

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

		if (dr->hasEntity()){
			Entity * e = dr->getEntityPtr();

			std::getline(in, str);
			std::getline(in, str);

			int nSubCol = std::stoi(str);

			iRect top;
			std::getline(in, str, ' ');
			top.x=std::stoi(str)+x;

			std::getline(in, str, ' ');
			top.y=std::stoi(str)+y;

			std::getline(in, str, ' ');
			top.w=std::stoi(str);

			std::getline(in, str, ' ');
			top.h=std::stoi(str);

			e->setTop(top);

			for (int i=0; i<nSubCol; i++){
				iRect tmp;
				std::getline(in, str, ' ');
				tmp.x=std::stoi(str)+x;

				std::getline(in, str, ' ');
				tmp.y=std::stoi(str)+y;

				std::getline(in, str, ' ');
				tmp.w=std::stoi(str);

				std::getline(in, str, ' ');
				tmp.h=std::stoi(str);

				e->addSub(tmp);
			}
		}
   }
   catch (std::ifstream::failure e){
      printf("Syntax Error in geometry file.\n");
      return false;
   }

   return true;
}

void update(){
	move();
}

void move(){
	std::vector<Entity>::iterator eVec;
	for (eVec=entities.begin(); eVec!=entities.end(); eVec++)
		eVec->move(entities);
}

void closeShader(){
	glDeleteProgram(shader.getProgramID());
}

void handleEvent(SDL_Event& e){
	playerPtr->handleEvent(e);
}

void render(){
   glClear(GL_COLOR_BUFFER_BIT);

   std::vector<Drawable>::iterator drIter;
   for (drIter = drawables.begin(); drIter != drawables.end(); drIter++){
		drIter->getEntityMV();
      if (drIter->isVisible()){
         shader.bind();
         shader.updateMV(drIter->getMVPtr());
         shader.updateColor(drIter->getColorPtr());

         glEnableVertexAttribArray(shader.getPosHandle());
         glBindBuffer(GL_ARRAY_BUFFER, drIter->getVBO());
         glVertexAttribPointer(shader.getPosHandle(), 2, GL_FLOAT, GL_FALSE,
                               2*sizeof(GL_FLOAT), NULL);

         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, drIter->getIBO());
         glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);
         glDisableVertexAttribArray(shader.getPosHandle());
         shader.unbind();
      }
   }
}
