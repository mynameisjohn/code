//I ripped this off of lazyfoo. Thanks. 

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>
#include "JShader.h"
#include "Drawable.h"

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
int mVelX, mVelY, mPosX, mPosY, DOT_VEL=10;
//OpenGL context
SDL_GLContext gContext;

//Render flag
bool gRenderQuad = true;

std::pair< JShader,std::vector<Drawable> > shadedObjs;

JShader shader;
std::vector<Drawable> drawables;

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
/*	
	//Use Vsync
	if( SDL_GL_SetSwapInterval(1) < 0 ){
		printf( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
	}
*/
	//Initialize OpenGL
	if( !initGL()){
		printf( "Unable to initialize OpenGL!\n" );
		return false;
	}

	return true;
}

void move(){
	shadedObjs.second[0].leftMultMV(glm::translate(glm::vec3(mVelX,mVelY,0.f)));
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

	glm::mat4 proj = glm::ortho<GLfloat>(0.0,400.f, 300.f, 0.0, 1.0, -1.0);
	shader.updateProj(glm::value_ptr(proj));

	Drawable square;
	shader.updateMV(square.getMVPtr());
	shader.updateColor(square.getColorPtr());

	shader.unbind();

	drawables.push_back(square);

	shadedObjs.first = shader;
	shadedObjs.second = drawables;

	initGeom();
	
	shader.unbind();
	
	glClearColor( 0.f, 0.f, 0.f, 1.f );
	
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

	GLuint tmpVBO, tmpIBO;	

   //Create VBO
   glGenBuffers( 1, &tmpVBO );
   glBindBuffer( GL_ARRAY_BUFFER, tmpVBO );
   glBufferData( GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW );

   //Create IBO
   glGenBuffers( 1, &tmpIBO );
   glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, tmpIBO );
   glBufferData( GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW );

	shadedObjs.second[0].setVBO(tmpVBO);
	shadedObjs.second[0].setIBO(tmpIBO);
}

void handleKeys( unsigned char key, int x, int y )
{
	//Toggle quad
	if( key == 'q' )
	{
		gRenderQuad = !gRenderQuad;
	}
	if (key == 'w')
		tY-=10;
	if (key == 'a')
      tX-=10;
	if (key == 's')
      tY+=10;
	if (key == 'd')
      tX+=10;
}

void update()
{
	//No per frame update needed
}

void handleEvent(SDL_Event& e){
	//If a key was pressed
   if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= DOT_VEL; break;
            case SDLK_DOWN: mVelY += DOT_VEL; break;
            case SDLK_LEFT: mVelX -= DOT_VEL; break;
            case SDLK_RIGHT: mVelX += DOT_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += DOT_VEL; break;
            case SDLK_DOWN: mVelY -= DOT_VEL; break;
            case SDLK_LEFT: mVelX += DOT_VEL; break;
            case SDLK_RIGHT: mVelX -= DOT_VEL; break;
        }
    }
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
		//shadedObjs.second[0].setMV(glm::translate(glm::vec3(0.5f*SCREEN_WIDTH+(GLfloat)tX,0.5f*SCREEN_HEIGHT+(GLfloat)tY,0.f)));
		shadedObjs.first.updateMV(shadedObjs.second[0].getMVPtr());
		shadedObjs.second[0].setColor(0.5f, 1.f, 0.f);
		shadedObjs.first.updateColor(shadedObjs.second[0].getColorPtr());
		//Enable vertex position
		glEnableVertexAttribArray( shadedObjs.first.getPosHandle() );

		//Set vertex data
		glBindBuffer( GL_ARRAY_BUFFER, shadedObjs.second[0].getVBO() );
		glVertexAttribPointer(shadedObjs.first.getPosHandle(), 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL );

		//Set index data and render
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, shadedObjs.second[0].getIBO() );
		glDrawElements( GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL );

		//Disable vertex position
		glDisableVertexAttribArray(shadedObjs.first.getPosHandle());

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
				
				handleEvent(e);
			}
			move();
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
