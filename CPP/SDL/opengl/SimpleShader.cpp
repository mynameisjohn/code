#include "SimpleShader.h"

SimpleShader::SimpleShader(){
	mPosAddr = 0;
	mColorAddr = 0;
	mProjMatAddr = 0;
	mMVMatAddr = 0;
	mVS = 0;
	mFS = 0;
}

bool SimpleShader::loadProgram(){
	if (!mVS || !mFS){
		printf("Missing vertex or fragment shader. \n");
		return false;
	}
	
	mProgramID = glCreateProgram();
	glAttachShader(mProgramID, mVS);
	glAttachShader(mProgramID, mFS);
	glLinkProgram(mProgramID);

	GLint success = GL_TRUE;
	glGetProgramiv(mProgramID, GL_LINK_STATUS, &success);
	if (success != GL_TRUE){
		printf("Error linking shader program %d. \n", mProgramID);
		printProgramLog(mProgramID);
		mProgramID = 0;
		return false;
	}

	mPosAddr = glGetAttribLocation(mProgramID, "vPosition");
   if (mPosAddr == -1)
      printf("%s is not a valid shader program variable.\n","vPosition");

	mColorAddr = glGetUniformLocation(mProgramID, "fColor");
	if (mColorAddr == -1)
		printf("%s is not a valid shader program variable.\n","fColor");

	mProjMatAddr = glGetUniformLocation(mProgramID, "projMat");
   if (mProjMatAddr == -1)
      printf("%s is not a valid shader program variable.\n","projMat");

	mMVMatAddr = glGetUniformLocation(mProgramID, "MVMat");
   if (mMVMatAddr == -1)
      printf("%s is not a valid shader program variable.\n","MVMat");

	return true;
}

void SimpleShader::loadVert(std::string vertStr){
	mVS = loadShaderFromFile(vertStr,GL_VERTEX_SHADER);
   if (mVS == 0)
      printf("Invalid vertex shader.\n");
}

void SimpleShader::loadFrag(std::string fragStr){
   mFS = loadShaderFromFile(fragStr,GL_VERTEX_SHADER);
   if (mFS == 0)
      printf("Invalid fragment shader.\n");
}

void SimpleShader::setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a){
	glUniform4f(mColorAddr, r, g, b, a);
}

void SimpleShader::setProj(glm::mat4 matrix){
	mProjMat = matrix;
}

void SimpleShader::setMV(glm::mat4 matrix){
	mMVMat = matrix;
}

void SimpleShader::leftMultProj(glm::mat4 matrix){
	mProjMat = matrix * mProjMat;
}

void SimpleShader::leftMultMV(glm::mat4 matrix){
   mMVMat = matrix * mMVMat;
}

void SimpleShader::updateProj(){
	glUniformMatrix4fv(mProjMatAddr, 1, GL_FALSE, glm::value_ptr(mProjMat));
}

void SimpleShader::updateMV(){
   glUniformMatrix4fv(mProjMatAddr, 1, GL_FALSE, glm::value_ptr(mMVMat));
}

GLint getPosAddr(){
	return mPosAddr;
}
