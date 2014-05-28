/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

//Using SDL, SDL OpenGL, GLEW, standard IO, file streams, and strings
#include <GL/gl.h>
#include <GL/glew.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdio.h>
#include <string>
#include <fstream>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "SimpleShader.h"
#include "ShaderProgram.h"

#define VERT_SHADER "shaders/simpleVert.glsl"
#define FRAG_SHADER "shaders/simpleFrag.glsl"


//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int tX=0, tY=0;

//Starts up SDL, creates window, and initializes OpenGL
bool init();

//Initializes rendering program and clear color
bool initGL();

//Initialize Simple Geometry
void initGeom();

//Input handler
void handleKeys( unsigned char key, int x, int y );

//Per frame update
void update();

//Renders quad to the screen
void render();

//Frees media and shuts down SDL
void close();

//Shader loading utility programs
void printProgramLog( GLuint program );
void printShaderLog( GLuint shader );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//OpenGL context
SDL_GLContext gContext;

//Render flag
bool gRenderQuad = true;

//Graphics program
GLuint gProgramID = 0;
GLint gVertexPos2DLocation = -1;
GLuint gVBO = 0;
GLuint gIBO = 0;

SimpleShader shader;

bool init()
{
	//Init SDL Video
	if (SDL_Init( SDL_INIT_VIDEO ) < 0){
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return false;
	}
	
	//Init SDL+OpenGL Context
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	//Create Window
	gWindow = SDL_CreateWindow("SDL Tutorial", 
										SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
										SCREEN_WIDTH, SCREEN_HEIGHT, 		
										SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (gWindow == NULL){
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError());
      return false;
   }

	//Create Context from Window
	gContext = SDL_GL_CreateContext(gWindow);
	if( gContext == NULL ){
		printf("OpenGL context was not created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	//Initialize GLEW
   glewExperimental = GL_TRUE;
   GLenum glewError = glewInit();
   if( glewError != GLEW_OK ){
      printf( "Error initializing GLEW! %s\n", glewGetErrorString(glewError));
		return false;
   }
	
	//Use Vsync
	if( SDL_GL_SetSwapInterval(1) < 0 ){
		printf( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
	}

	//Initialize OpenGL
	if( !initGL()){
		printf( "Unable to initialize OpenGL!\n" );
		return false;
	}

	return true;
}

bool initGL()
{
	//Load Vertex/Fragment Shader files
	if (!shader.loadVert(VERT_SHADER) ||
		 !shader.loadFrag(FRAG_SHADER))
		return false;

	//Generate Shader Program
	if (!shader.loadProgram())
		return false;
	shader.bind();
	shader.setProj(glm::ortho<GLfloat>(0.0,SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0));
	shader.updateProj();

	shader.setMV(glm::mat4()); 
	shader.updateMV();
	shader.unbind();
	//Initialize clear color
	glClearColor( 0.f, 0.f, 0.f, 1.f );

	//Initialize Simple Geometry
	initGeom();

	return true;
}

void initGeom(){
	//VBO data
   GLfloat vertexData[] =
   {
      -50.f, -50.f,
       50.f, -50.f,
       50.f,  50.f,
      -50.f,  50.f
   };

   //IBO data
   GLuint indexData[] = { 0, 1, 2, 3 };

   //Create VBO
   glGenBuffers( 1, &gVBO );
   glBindBuffer( GL_ARRAY_BUFFER, gVBO );
   glBufferData( GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW );

   //Create IBO
   glGenBuffers( 1, &gIBO );
   glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, gIBO );
   glBufferData( GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW );
}

void handleKeys( unsigned char key, int x, int y )
{
	//Toggle quad
	if( key == 'q' )
	{
		gRenderQuad = !gRenderQuad;
	}
	if (key == 'w')
		tY++;
	if (key == 'a')
      tX--;
	if (key == 's')
      tY--;
	if (key == 'd')
      tX++;
}

void update()
{
	//No per frame update needed
}

void render()
{
	//Clear color buffer
	glClear( GL_COLOR_BUFFER_BIT );
	
	//Render quad
	if( gRenderQuad )
	{
		//Bind program
		shader.bind();
		shader.setMV(glm::translate(glm::vec3(0.5f*SCREEN_WIDTH,0.5f*SCREEN_HEIGHT,0.f)));
		shader.updateMV();
		shader.setColor(0.5f, 1.f, 0.f);
		//Enable vertex position
		glEnableVertexAttribArray( shader.getPosAddr() );

		//Set vertex data
		glBindBuffer( GL_ARRAY_BUFFER, gVBO );
		glVertexAttribPointer(shader.getPosAddr(), 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL );

		//Set index data and render
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, gIBO );
		glDrawElements( GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL );

		//Disable vertex position
		glDisableVertexAttribArray(shader.getPosAddr());

		//Unbind program
		//glUseProgram( NULL );
		shader.unbind();
	}
}

void close()
{
	//Deallocate program
	glDeleteProgram( shader.getProgramID() );

	//Destroy window	
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

void printProgramLog( GLuint program )
{
	//Make sure name is shader
	if( glIsProgram( program ) )
	{
		//Program log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;
		
		//Get info string length
		glGetProgramiv( program, GL_INFO_LOG_LENGTH, &maxLength );
		
		//Allocate string
		char* infoLog = new char[ maxLength ];
		
		//Get info log
		glGetProgramInfoLog( program, maxLength, &infoLogLength, infoLog );
		if( infoLogLength > 0 )
		{
			//Print Log
			printf( "%s\n", infoLog );
		}
		
		//Deallocate string
		delete[] infoLog;
	}
	else
	{
		printf( "Name %d is not a program\n", program );
	}
}

void printShaderLog( GLuint shader )
{
	//Make sure name is shader
	if( glIsShader( shader ) )
	{
		//Shader log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;
		
		//Get info string length
		glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &maxLength );
		
		//Allocate string
		char* infoLog = new char[ maxLength ];
		
		//Get info log
		glGetShaderInfoLog( shader, maxLength, &infoLogLength, infoLog );
		if( infoLogLength > 0 )
		{
			//Print Log
			printf( "%s\n", infoLog );
		}

		//Deallocate string
		delete[] infoLog;
	}
	else
	{
		printf( "Name %d is not a shader\n", shader );
	}
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event e;
		
		//Enable text input
		SDL_StartTextInput();

		//While application is running
		while( !quit )
		{
			//Handle events on queue
			while( SDL_PollEvent( &e ) != 0 )
			{
				//User requests quit
				if( e.type == SDL_QUIT )
				{
					quit = true;
				}
				//Handle keypress with current mouse position
				else if( e.type == SDL_TEXTINPUT )
				{
					int x = 0, y = 0;
					SDL_GetMouseState( &x, &y );
					handleKeys( e.text.text[ 0 ], x, y );
				}
			}

			//Render quad
			render();
			
			//Update screen
			SDL_GL_SwapWindow( gWindow );
		}
		
		//Disable text input
		SDL_StopTextInput();
	}

	//Free resources and close SDL
	close();

	return 0;
}
