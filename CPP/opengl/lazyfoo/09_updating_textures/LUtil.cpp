/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/
//Version: 009

#include "LUtil.h"
//#include <IL/il.h>
//#include <IL/ilu.h>
<<<<<<< HEAD
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "LTexture.h"
=======
#include "LTexture.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
>>>>>>> 75244c4ba46194045ae98710e59c4400b318b04d

//Circle image
LTexture gCircleTexture;

bool initGL()
{
    //Set the viewport
    glViewport( 0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT );

    //Initialize Projection Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0 );

    //Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    //Initialize clear color
    glClearColor( 0.f, 0.f, 0.f, 1.f );

    //Enable texturing
    glEnable( GL_TEXTURE_2D );

    //Check for error
    GLenum error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        return false;
    }
<<<<<<< HEAD

    //Initialize DevIL and DevILU
    //ilInit();
    //iluInit();
    //ilClearColour( 255, 255, 255, 000 );

	 SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG) 
/*
=======
/*
    //Initialize DevIL and DevILU
    ilInit();
    iluInit();
    ilClearColour( 255, 255, 255, 000 );

>>>>>>> 75244c4ba46194045ae98710e59c4400b318b04d
    //Check for error
    ILenum ilError = ilGetError();
    if( ilError != IL_NO_ERROR )
    {
        printf( "Error initializing DevIL! %s\n", iluErrorString( ilError ) );
        return false;
    }
*/
<<<<<<< HEAD
=======

	 SDL_Init(SDL_INIT_VIDEO);
	 IMG_Init(INIT_IMG_PNG);

>>>>>>> 75244c4ba46194045ae98710e59c4400b318b04d
    return true;
}

bool loadMedia()
{
    //Load texture
    if( !gCircleTexture.loadTextureFromFile( "09_updating_textures/circle.png" ) )
    {
        printf( "Unable to load circle texture!\n" );
        return false;
    }

    //Lock texture for modification
    gCircleTexture.lock();

    //Calculate target color
    GLuint targetColor;
    GLubyte* colors = (GLubyte*)&targetColor;
<<<<<<< HEAD
    colors[ 0 ] = 000;
    colors[ 1 ] = 255;
    colors[ 2 ] = 255;
    colors[ 3 ] = 255;
=======
    colors[ 0 ] = 0x00;
    colors[ 1 ] = 0xFF;
    colors[ 2 ] = 0xFF;
    colors[ 3 ] = 0xFF;
>>>>>>> 75244c4ba46194045ae98710e59c4400b318b04d

    //Replace target color with transparent black
    GLuint* pixels = gCircleTexture.getPixelData32();
    GLuint pixelCount = gCircleTexture.textureWidth() * gCircleTexture.textureHeight();
    for( int i = 0; i < pixelCount; ++i )
    {
        if( pixels[ i ] == targetColor )
        {
            pixels[ i ] = 0;
        }
    }

    //Diagonal Lines
    for( int y = 0; y < gCircleTexture.imageHeight(); ++y )
    {
        for( int x = 0; x < gCircleTexture.imageWidth(); ++x )
        {
            if( y % 10 != x % 10 )
            {
                gCircleTexture.setPixel32( x, y, 0 );
            }
        }
    }

    //Update texture
    gCircleTexture.unlock();

    return true;
}

void update()
{

}

void render()
{
    //Clear color buffer
    glClear( GL_COLOR_BUFFER_BIT );

    //Render circle
    gCircleTexture.render( ( SCREEN_WIDTH - gCircleTexture.imageWidth() ) / 2.f, ( SCREEN_HEIGHT - gCircleTexture.imageHeight() ) / 2.f );

    //Update screen
    glutSwapBuffers();
}
