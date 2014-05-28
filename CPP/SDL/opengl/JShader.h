#ifndef J_SHADER_H
#define J_SHADER_H

#include "ShaderProgram.h"

class JShader : public ShaderProgram{
	public:
		JShader();
		bool loadProgram();
		bool loadVert(std::string vertStr);
		bool loadFrag(std::string fragStr);
		void updateProj(GLfloat * proj);
		void updateMV(GLfloat * MV);
		void updateColor(GLfloat * color);
	private:
		GLint mMVHandle, mProjHandle, mColorHandle, mPosHandle;
		GLuint mVS, mFS;
};

#endif
