#ifndef J_SHADER_H
#define J_SHADER_H

#include "ShaderProgram.h"

class JShader : public ShaderProgram{
	public:
		JShader();                         //Default Constructor
		bool loadProgram();                //Load Program
		bool loadVert(std::string vertStr);//Load Vert Shader from string
		bool loadFrag(std::string fragStr);//Load Frag Shader from string
		GLint getPosHandle();              //get vertex position handle
		void updateProj(GLfloat * proj);   //update proj, send to GPU
		void updateMV(GLfloat * MV);       //update MV, send to GPU
		void updateColor(GLfloat * color); //update color, send to GPU
	private:
		GLint mMVHandle;   //Handle to MV matrix
		GLint mProjHandle; //Handle to Projection Matrix
		GLint mColorHandle;//Handle to Frag Color (needed?)
		GLint mPosHandle;  //Handle to Vertex Position
		GLuint mVS, mFS;   //References to vertex and fragment shaders
};

#endif
