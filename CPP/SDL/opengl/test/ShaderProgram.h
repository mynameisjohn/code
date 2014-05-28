//This class was blatantly 
//ripped off from LazyFoo.
//sorry. 

#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "OGLincludes.h"
#include <string>
#include <fstream>

class ShaderProgram
{
	public:
		//default constructor
		ShaderProgram();

		//base destructor
		virtual ~ShaderProgram();

		//virtual load
		virtual bool loadProgram() = 0;

		//virtual free
		virtual void freeProgram();

		//bind shader
		bool bind();

		//unbind shader
		void unbind();

		//get program id
		GLuint getProgramID();

	protected:
		//print out program log to console
		void printProgramLog( GLuint program );

		//print out shsader log to console
		void printShaderLog( GLuint shader );

		//load shader from text file
		GLuint loadShaderFromFile( std::string path, GLenum shaderType );

		//Program ID
		GLuint mProgramID;
};

#endif
