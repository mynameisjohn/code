#ifndef SIMPLE_SHADER_H
#define SIMPLE_SHADER_H

#include "ShaderProgram.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

class SimpleShader : public ShaderProgram{
	public:
		SimpleShader();
		bool loadProgram();
		bool loadVert(std::string vertStr);
		bool loadFrag(std::string fragStr);
		void setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a=1.f);
		void setProj(glm::mat4 matrix);
		void setMV(glm::mat4 matrix);
		void leftMultProj(glm::mat4 matrix);
		void leftMultMV(glm::mat4 matrix);
		void updateProj();
		void updateMV();
		GLint getPosAddr();	
	private:
		GLint mColorAddr, mPosAddr;
		glm::mat4 mProjMat, mMVMat;
		GLint mProjMatAddr, mMVMatAddr;
		GLuint mVS, mFS;
};

#endif
