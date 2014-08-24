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
		GLuint getTexCoordHandle();
		GLuint getTexHandle();
		//void updateProj(GLfloat * proj);   //update proj, send to GPU
		//void updateMV(GLfloat * MV);       //update MV, send to GPU
		void updateMVP(GLfloat * MVP);
		void updateColor(GLfloat * color); //update color, send to GPU
		void updateSampler();
	private:
		GLuint mTexCoordHandle; //Handle to Texture Coordinates
		//GLuint mTexHandle;      //Handle to texture sampler
		//GLuint texture;         //Handle to texture
		GLint mMVPHandle;   //Handle to MVP matrix
		//GLint mProjHandle; //Handle to Projection Matrix
		GLint mColorHandle;//Handle to Frag Color (needed?)
		GLint mPosHandle;  //Handle to Vertex Position
		GLuint mVS, mFS;   //References to vertex and fragment shaders
};

#endif
