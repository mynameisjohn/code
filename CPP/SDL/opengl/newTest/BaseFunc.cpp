#include "BaseFunc.h"

//Globals...
std::vector<ShadeCollective> SC;
bool gRenderQuad=true;

bool init(SDL_Window * mWindow, SDL_GLContext * mCtx)
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
   mWindow = SDL_CreateWindow("SDL Tutorial",
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
   if (mWindow == NULL){
      printf( "Window could not be created! SDL Error: %s\n", SDL_GetError());
      return false;
   }

   //Create Context from Window
   *mCtx = SDL_GL_CreateContext(mWindow);
   if( mCtx == NULL ){
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
	JShader shader;
	Drawable square;

   //Load Vertex/Fragment Shader files
   if (!shader.loadVert(VERT_SHADER) ||
       !shader.loadFrag(FRAG_SHADER))
      return false;

   //Generate Shader Program
   if (!shader.loadProgram())
      return false;


   shader.bind();

   glm::mat4 proj = glm::ortho<GLfloat>(0.0,SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0);
   shader.updateProj(glm::value_ptr(proj));

   shader.updateMV(square.getMVPtr());
   shader.updateColor(square.getColorPtr());

   shader.unbind();

   initGeom(&square);

	std::vector<Drawable> d;
	d.push_back(square);
	ShadeCollective sc = {shader,d};
	SC.push_back(sc);

   glClearColor( 0.f, 0.f, 0.f, 1.f );

   return true;
}

void initGeom(Drawable * square){
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

   square->setVBO(tmpVBO);
   square->setIBO(tmpIBO);
}

void handleKeys( unsigned char key, int x, int y )
{
   //Toggle quad
   if( key == 'q' )
   {
      gRenderQuad = !gRenderQuad;
   }/*
   if (key == 'w')
      tY++;
   if (key == 'a')
      tX--;
   if (key == 's')
      tY--;
   if (key == 'd')
      tX++;
*/
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
		SC[0].shader.bind();
/*      SC[0].drawables[0].setMV(glm::translate(glm::vec3(0.5f*SCREEN_WIDTH,0.5f*SCREEN_HEIGHT,0.f)));
      SC[0].shader.updateMV(SC[0].drawables[0].getMVPtr());
      SC[0].drawables[0].setColor(0.5f, 1.f, 0.f);
      SC[0].shader.updateColor(SC[0].drawables[0].getColorPtr());
      //Enable vertex position
      glEnableVertexAttribArray( SC[0].shader.getPosHandle() );

      //Set vertex data
      glBindBuffer( GL_ARRAY_BUFFER, SC[0].drawables[0].getVBO() );
      glVertexAttribPointer(SC[0].shader.getPosHandle(), 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL );

      //Set index data and render
      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, SC[0].drawables[0].getIBO() );
      glDrawElements( GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL );

      //Disable vertex position
      glDisableVertexAttribArray(SC[0].shader.getPosHandle());
*/
      //Unbind program
      //glUseProgram( NULL );
      SC[0].shader.unbind();
   }
}

void closeGL(){
	glDeleteProgram(SC[0].shader.getProgramID());
}

/*
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
*/
