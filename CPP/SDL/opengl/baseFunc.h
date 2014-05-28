#include "OGLincludes.h"
#include "SDLincludes.h"
#include "glm/gtx/transform.hpp"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

//Shader
SimpleShader shader;

//VBO
GLuint gVBO = NULL;
GLuint gIBO = NULL;

bool init(SDL_Window window&, SDL_GLContext context){
	if (SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("SDL did not initialize. %s\n", SDL_GetError());
		return false;
	}

	//Use OpenGL 3.1 core
   SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
   SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
   SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

	window = SDL_CreateWindow("OpenGL+SDL Test", 
										SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
										SCREEN_WIDTH, SCREEN_HEIGHT, 
										SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
	if (window == NULL){
		printf("Window was not opened. %s\n", SDL_GetError());
		return false;
	}

	context = SDL_GL_CreateContext(window);
	if (context == NULL){
		printf("OpenGL context was not created. %s\n", SDL_GetError());
      return false;
   }

	//vsync
	if (SDL_GL_SetSwapInterval(1) < 0)
		printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());

	if (!initGL()){
		printf("Could not initialize OpenGL.\n");
		return false;
	}

	initGeom();
	
	return true;
}

bool initGL(){
	glewExperimental = GL_TRUE;
   GLenum glewError = glewInit();
   if (glewError != GLEW_OK){
      printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
		return false;
	}

   if( !GLEW_VERSION_2_1 ){
       printf( "OpenGL 2.1 not supported!\n" );
       return false;
   }
	
	shader.loadVertStr("shaders/simpleVert.glsl");
	shader.loadFragStr("shaders/simpleFrag.glsl");
	if (!shader.loadProgram()){
		printf("Error initializing shaders. \n");
		return false;
	}

	shader.setMV(glm::mat4());
	shader.setProj(glm::ortho<GLfloat>(0.0, SCREEN_WIDTH, 0.0, SCREEN_HEIGHT, 0.0, 1.0, -1.0));

	shader.updateProj();
	shader.updateMV();

	glClearColor(0.f, 0.f, 0.f, 1.f);

	return true;
}

void initGeom(){
	GLfloat vertexData[] = {
   -0.5f,-0.5f,
   -0.5f,0.5f,
    0.5f,0.5f,
    0.5f,-0.5f
   };

	GLuint indexData[] = {
	0, 1, 
	2, 3
	};
	
	glGenBuffers(1, &gVBO);
	glBindBuffer(GL_ARRAY_BUFFER, gVBO);
	glBufferData(GL_ARRAY_BUFFER, 2*4*sizeof(GLfloat), vertexData, GL_STATIC_DRAW);
	
	glGenBuffers(1, &gIBO);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gVBO);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(GLuint), indexData, GL_STATIC_DRAW);
}

void handleInput(unsigned char key, int x, int y){
	if (key == 'q')
		gRenderQuad = !gRenderQuad;
}

void update(){

}

void render(){
	glClear(GL_COLOR_BUFFER_BIT);

	if (gRenderQuad){
		shader.setMV(glm::translate(<GLfloat>(SCREEN_WIDTH/2.f, SCREEN_HEIGHT/2.f, 0.f));
		shader.updateMV();
		shader.setColor(1.f, 1.f, 1.f);
		shader.bind();
		glEnableVertexAttribArray(shader.getPosHandle());
      glBindBuffer( GL_ARRAY_BUFFER, gVBO );
      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, gIBO );
      glDrawElements( GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL );
		glDisableVertexAttribArray(shader.getPosHandle());
		shader.unbind();
	}
}
