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
	glm::mat4 proj = glm::ortho<GLfloat>(0.0,
								SPACE_WIDTH, SPACE_HEIGHT, 0.0, 1.0, -1.0);
	shader.updateProj(glm::value_ptr(proj));
/*
	std::vector<bool> xFirst;
   xFirst.push_back(false);
	//Initialize Player
	Drawable player_dr;
	Player player;
	player.setXFirst(xFirst);
	player.setWalls(0, 0, SPACE_WIDTH, SPACE_HEIGHT);
	entities.push_back(player);
	player_dr.setEntity((Entity *)&entities.back());
	drawables.push_back(player_dr);
	//initSquare(drawables.back(), 300, 100);
	playerPtr = (Player *)(&entities.back());

	//Initialize other squares
	Entity sq1_e;
	sq1_e.setXFirst(xFirst);
	sq1_e.setWalls(0, 0, SPACE_WIDTH, SPACE_HEIGHT);
	entities.push_back(sq1_e);
	Drawable sq1_dr;
	sq1_dr.setEntity((Entity *)&entities.back());
	drawables.push_back(sq1_dr);
	//initSquare(drawables.back(), 200, 200);

	Entity sq2_e;
   sq2_e.setXFirst(xFirst);
   sq2_e.setWalls(0, 0, SPACE_WIDTH, SPACE_HEIGHT);
   entities.push_back(sq2_e);
   Drawable sq2_dr;
   sq1_dr.setEntity((Entity *)&entities.back());
   drawables.push_back(sq2_dr);
	//initSquare(drawables.back(), 200, 0);

	//Initialize Scenery
	Collider rect_sc;
	scenery.push_back(rect_sc);
	Drawable rect_dr;
	rect_dr.setCollider(&scenery.back());
	drawables.push_back(rect_dr);
	//initSquare(drawables.back(), 0, 200);
	printf("how are ya\n");
*/


	//For the purpose of this example, the drawables will be
	//	+ 1 Rectangle (passive)
	// + 2 Triangles (aggressive)
	// + 2 Square (player)

	Drawable rect_dr, tri1_dr, tri2_dr, square_dr;
	Entity tri1_e, tri2_e;
	Player square_e;
	Collider rect_sc;

	/*iRect top;
	top.x=250; top.y=150; //SPACE_HEIGHT/2;
	top.w=5; top.h=200;
	rect_sc.setTop(top);*/
	scenery.push_back(rect_sc);

	std::vector<bool> xFirst;
	xFirst.push_back(false);
	tri1_e.setXFirst(xFirst);
	tri2_e.setXFirst(xFirst);
	square_e.setXFirst(xFirst);
	/*
	rect_dr.setColor(1.f, 0.2f, 0.2f);
	tri1_dr.setColor(1.f, 0.3f, 0.f);
	tri2_dr.setColor(0.f, 0.5f, 0.8f);
	square_dr.setColor(0.1f, 0.3f, 0.7f);
   */
	tri1_e.setWalls(0, 0, SPACE_WIDTH, SPACE_HEIGHT);
	tri2_e.setWalls(0, 0, SPACE_WIDTH, SPACE_HEIGHT);
	square_e.setWalls(0, 0, SPACE_WIDTH, SPACE_HEIGHT);

   drawables.push_back(rect_dr);   //This rect isn't an entity
   drawables.push_back(tri1_dr);   entities.push_back(tri1_e);
   drawables.push_back(tri2_dr);   entities.push_back(tri2_e);
   drawables.push_back(square_dr); entities.push_back(square_e);

	drawables[0].setCollider(&scenery[0]);
	drawables[1].setEntity(&entities[0]);
	drawables[2].setEntity(&entities[1]);
	drawables[3].setEntity(&entities[2]);

	playerPtr = (Player *)(&entities.back());
/*
	initSquare(drawables[0], 3*SPACE_WIDTH/4, SPACE_HEIGHT/2);
	initSquare(drawables[1], SPACE_WIDTH/4, SPACE_HEIGHT/2);
	initSquare(drawables[2], 3*SPACE_WIDTH/4, SPACE_HEIGHT/4);
	initSquare(drawables[3], 0, SPACE_HEIGHT/2);
	printf("fine\n");
*/

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



/*	const int misc=1, player=2, scenery=3;

	addSquare(3*SPACE_WIDTH/4, SPACE_HEIGHT/2, misc);
	addSquare(0, SPACE_HEIGHT/2, misc);
	addSquare(200, 100, scenery);
	addSquare(350, 350, player);
*/
	glClearColor(0.2f, 0.2f, 0.2f, 1.f);

	return true;
}

bool addSquare(int x, int y, int type){
	const GLfloat vertices[4][2] = {
		{0.f, 0.f}, {40.f, 0.f},
		{0.f, 40.f}, {40.f, 40.f}
	};
   const GLfloat texCoords[4][2] = {
		{0.f, 0.f}, {1.f, 0.f},
		{0.f, 1.f}, {1.f, 1.f}
	};

	const GLuint indices[4] = {0, 1, 2, 3};

	Drawable dr;

	GLuint tmpVAO;
   glGenVertexArrays(1, &tmpVAO);
   glBindVertexArray(tmpVAO);

	GLuint buffers[3];
	glGenBuffers(3, buffers);

	//vertices
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, 2*4*sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(shader.getPosHandle());
	glVertexAttribPointer(shader.getPosHandle(), 2, GL_FLOAT, 0, 0, 0);

	//tex coords
	glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, 2*4*sizeof(GLfloat), texCoords, GL_STATIC_DRAW);
	glEnableVertexAttribArray(shader.getTexCoordHandle());
	glVertexAttribPointer(shader.getTexCoordHandle(), 2, GL_FLOAT, 0, 0, 0);

	//indices
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, buffers[2] );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indices, GL_STATIC_DRAW );

	dr.setVAO(tmpVAO);
	glBindVertexArray(0);
	dr.leftMultMV(glm::translate(glm::vec3((GLfloat)x, (GLfloat)y, 0.f)));
	drawables.push_back(dr);

	iRect top;
	top.x=x; top.y=y;
	top.w=40; top.h=40;

	if (type == 1){
		std::vector<bool> xFirst;
		xFirst.push_back(false);
		Entity e;
		e.setTop(top);
		e.setWalls(0, 0, SPACE_WIDTH, SPACE_HEIGHT);
		e.setXFirst(xFirst);
		entities.push_back(e);
		drawables.back().setEntity(&(entities.back()));
		drawables.back().setColor(1.f, 0.2f, 0.1f);
	}
	else if (type == 2){
		std::vector<bool> xFirst;
      xFirst.push_back(false);
      Player p;
		p.setTop(top);
      p.setWalls(0, 0, SPACE_WIDTH, SPACE_HEIGHT);
      p.setXFirst(xFirst);
      entities.push_back(p);
      drawables.back().setEntity((Entity *)(&(entities.back())));
		playerPtr = (Player *)(&(entities.back()));
		drawables.back().setColor(0.2f, 1.f, 0.1f);
	}
	else if (type == 3){
		Collider sc;
		sc.setTop(top);
		scenery.push_back(sc);
		drawables.back().setCollider(&(scenery.back()));
		drawables.back().setColor(0.1f, 0.2f, 1.f);
	}
	else
		return false;

	return tmpVAO>0;	
}

bool initSquare(Drawable& dr, int x, int y){
const GLfloat hardvertices[4][2] = {
         {0.f, 0.f}, {40.f, 0.f},
         {0.f, 40.f}, {40.f, 40.f}
      };
      const GLfloat hardtexCoords[4][2] = {
         {0.f, 0.f}, {1.f, 0.f},
         {0.f, 1.f}, {1.f, 1.f}
      };
      const GLuint hardindices[4] = {0, 1, 2, 3};



      const GLfloat texCoords[6][2] ={
        {0.0f, 0.0f},
        {1.0f, 0.0f},
         {0.f, 0.5f},
         {1.f, 0.5f},
        {0.0f, 1.0f},
        {1.0f, 1.0f}
      };
GLuint tmpVAO;
      glGenVertexArrays(1, &tmpVAO);
      glBindVertexArray(tmpVAO);

      GLuint buffers[3];
      glGenBuffers(3, buffers);

      //vertices
      glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
      glBufferData(GL_ARRAY_BUFFER, 2*4*sizeof(GLfloat), hardvertices, GL_STATIC_DRAW);
      glEnableVertexAttribArray(shader.getPosHandle());
      glVertexAttribPointer(shader.getPosHandle(), 2, GL_FLOAT, 0, 0, 0);

      //tex coords
      glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
      glBufferData(GL_ARRAY_BUFFER, 2*4*sizeof(GLfloat), hardtexCoords, GL_STATIC_DRAW);
      glEnableVertexAttribArray(shader.getTexCoordHandle());
      glVertexAttribPointer(shader.getTexCoordHandle(), 2, GL_FLOAT, 0, 0, 0);

      //indices
      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, buffers[2] );
      glBufferData( GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), hardindices, GL_STATIC_DRAW );

      glBindVertexArray(0);
      dr.leftMultMV(glm::translate(glm::vec3(x, y, 0)));
      iRect top;
      top.x=x; top.y=y;
      top.w=40; top.h=40;
      //shift(top, x, y);

      if (dr.hasEntity())
         dr.getEntityPtr()->setTop(top);
      else if (dr.hasCollider())
         dr.getColPtr()->setTop(top);


      dr.setVAO(tmpVAO);
	
	return true;
}

bool initGeom(Drawable * dr, std::string src, int x, int y){
/*   std::ifstream in;
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
         vertices[i*2]=(GLfloat)std::stof(str) + (GLfloat) x;
         std::getline(in, str, ' ');
         vertices[i*2+1]=(GLfloat)std::stof(str) + (GLfloat) y;
      }

      GLuint indices [nVert];

*/
		const GLfloat hardvertices[4][2] = {
			{0.f, 0.f}, {40.f, 0.f},
			{0.f, 40.f}, {40.f, 40.f}
		};
		const GLfloat hardtexCoords[4][2] = {
			{0.f, 0.f}, {1.f, 0.f},
			{0.f, 1.f}, {1.f, 1.f}
		};
	   const GLuint hardindices[4] = {0, 1, 2, 3};

	

		const GLfloat texCoords[6][2] ={
        {0.0f, 0.0f},
        {1.0f, 0.0f},
			{0.f, 0.5f},
			{1.f, 0.5f},
        {0.0f, 1.0f},
        {1.0f, 1.0f}
		};
/*
		for (int i=0; i<nVert; i++){
         std::getline(in, str, ' ');
         indices[i]=(GLuint)std::stoi(str);
      }

      GLuint tmpVBO, tmpIBO, tmpTBO;
*/
		GLuint tmpVAO;
		glGenVertexArrays(1, &tmpVAO);
		glBindVertexArray(tmpVAO);

		GLuint buffers[3];
		glGenBuffers(3, buffers);

		//vertices
		glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
		glBufferData(GL_ARRAY_BUFFER, 2*4*sizeof(GLfloat), hardvertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(shader.getPosHandle());
		glVertexAttribPointer(shader.getPosHandle(), 2, GL_FLOAT, 0, 0, 0);

		//tex coords
		glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
      glBufferData(GL_ARRAY_BUFFER, 2*4*sizeof(GLfloat), hardtexCoords, GL_STATIC_DRAW);
      glEnableVertexAttribArray(shader.getTexCoordHandle());
      glVertexAttribPointer(shader.getTexCoordHandle(), 2, GL_FLOAT, 0, 0, 0);

		//indices
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, buffers[2] );
      glBufferData( GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), hardindices, GL_STATIC_DRAW );
	
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


/*
		if (dr->hasEntity() || dr->hasCollider()){
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

			if (dr->hasEntity())
				dr->getEntityPtr()->setTop(top);
			else if (dr->hasCollider()){
				dr->getColPtr()->setTop(top);
			}

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

				if (dr->hasEntity())
			      dr->getEntityPtr()->setTop(top);
	         else if (dr->hasCollider())
		         dr->getColPtr()->setTop(top);
			}
		}
   }
   catch (std::ifstream::failure e){
      printf("Syntax Error in geometry file.\n");
      return false;
   }
*/
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

