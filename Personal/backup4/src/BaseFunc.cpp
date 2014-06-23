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
std::vector<Collider> scenery;
Player * playerPtr;
KeyboardHandler handler;

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
	glm::mat4 proj = glm::ortho<GLfloat>(
								 0.0,SPACE_WIDTH, SPACE_HEIGHT, 0.0, 1.0, -1.0); 
	shader.updateProj(glm::value_ptr(proj));

	int posHandle = shader.getPosHandle();
	int texCoordHandle = shader.getTexCoordHandle();

	initLevel();

	glClearColor(0.2f, 0.2f, 0.2f, 1.f);

	return true;
}

bool initLevel(){
	const int nPlayer = 1;
	const int nNPC = 2;
	const int nScenery = 1;
	const int nDrawables = nPlayer+nNPC+nScenery;

	drawables.clear();
	drawables.resize(nDrawables);

	//I REALIZE THE BEST SOLUTION WOULD BE TO WRITE A FUNCTION
	//THAT CREATES DRAWABLES AND ENTITIES TOGETHER. IT WAS
	//BUGGY AS FUCK, SO I GAVE UP. WOULD LOVE TO FIX IT. 
   Entity tri1_e, tri2_e;
   Player square_e;
   Collider rect_sc;

   scenery.push_back(rect_sc);

   std::vector<bool> xFirst;
   xFirst.push_back(false);
   tri1_e.setXFirst(xFirst);
   tri2_e.setXFirst(xFirst);
   square_e.setXFirst(xFirst);

   tri1_e.setWalls(0, 0, SPACE_WIDTH, SPACE_HEIGHT);
   tri2_e.setWalls(0, 0, SPACE_WIDTH, SPACE_HEIGHT);
   square_e.setWalls(0, 0, SPACE_WIDTH, SPACE_HEIGHT);

	entities.push_back(tri1_e);
	entities.push_back(tri2_e);
	entities.push_back(square_e);

   drawables[0].setCollider(&scenery[0]);
   drawables[1].setEntity(&entities[0]);
   drawables[2].setEntity(&entities[1]);
   drawables[3].setEntity(&entities[2]);

	playerPtr = (Player *)(&entities.back());
   //NOW INITGEOM STARTS

   if (!initSquare(&drawables[3], 3*SPACE_WIDTH/4, SPACE_HEIGHT/2)){
      printf("Error initializing geometry.\n");
      return false;
   }

   if (!initSquare(&drawables[2], 50, SPACE_HEIGHT/2)){
      printf("Error initializing geometry.\n");
      return false;
   }

   if (!initSquare(&drawables[1], 50, 50)){
      printf("Error initializing geometry.\n");
      return false;
   }

   if (!initRect(&drawables[0], 250, SPACE_HEIGHT/2)){
      printf("Error initializing geometry.\n");
      return false;
   }

	return true;
}

bool initSquare(Drawable * dr, int x, int y){
   const int nVert=4, dim=2, nIndices=4;
   const int vStride = 4*2*sizeof(GLint);
   const int tStride = 4*2*sizeof(GLfloat);
   const int iStride = 4*sizeof(GLuint);

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

   dr->leftMultMV(glm::translate(glm::vec3(x, y, 0)));
   iRect top;
   top.x=x; top.y=y;
   top.w=40; top.h=40;
   //shift(top, x, y);

   if (dr->hasEntity()){
      dr->getEntityPtr()->setTop(top);
      dr->setColor(0.1f, 0.3f, 0.6f);
   }
   else if (dr->hasCollider()){
      dr->getColPtr()->setTop(top);
      dr->setColor(0.4f, 0.6f, 0.2f);
   }

   dr->setVAO(tmpVAO);

   return true;
}

bool initRect(Drawable * dr, int x, int y){
   const int nVert=4, dim=2, nIndices=4;
   const int vStride = 4*2*sizeof(GLint);
   const int tStride = 4*2*sizeof(GLfloat);
   const int iStride = 4*sizeof(GLuint);

   const GLint vertices[nVert][dim] = {
      {0, 0}, {40, 0},
      {30, 80}, {70, 80}
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

   dr->leftMultMV(glm::translate(glm::vec3(x, y, 0)));

	iRect top;
   top.x=x; top.y=y;
   top.w=40; top.h=80;
   //shift(top, x, y);

   if (dr->hasEntity()){
      dr->getEntityPtr()->setTop(top);
      dr->setColor(0.1f, 0.3f, 0.6f);
   }
   else if (dr->hasCollider()){
      dr->getColPtr()->setTop(top);
      dr->setColor(0.4f, 0.6f, 0.2f);
   }

   dr->setVAO(tmpVAO);

   return true;
}

void update(){
	move();
}

void move(){
	std::vector<Entity>::iterator eVec;
	for (eVec=entities.begin(); eVec!=entities.end(); eVec++)
		eVec->move(entities, scenery);
}

void closeShader(){
	glDeleteProgram(shader.getProgramID());
}

void handleEvent(SDL_Event& e){
	if (e.key.repeat == 0 && (e.type == SDL_KEYUP || e.type == SDL_KEYDOWN))
		handler.handleKey((int)e.key.keysym.sym);
	playerPtr->handleEvent(&handler);
}

void render(){
   glClear(GL_COLOR_BUFFER_BIT);

   std::vector<Drawable>::iterator drIter;
   for (drIter = drawables.begin(); drIter != drawables.end(); drIter++){
		drIter->getEntityMV();
      shader.bind();
		if (drIter->isVisible()){
         //shader.bind();
         shader.updateMV(drIter->getMVPtr());
         shader.updateColor(drIter->getColorPtr());
			glBindVertexArray(drIter->getVAO());
			glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, NULL);
			//shader.unbind();
      }
		shader.unbind();
   }
}

