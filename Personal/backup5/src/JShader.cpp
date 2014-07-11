#include "JShader.h"

JShader::JShader(){
	mMVHandle = -1;
	mColorHandle = -1;
	mPosHandle = -1;
	mVS = 0;
	mFS = 0;
}

bool JShader::loadProgram(){
	if (!mVS){
		printf("Missing vertex shader\n");
		return false;
	}

	 if (!mFS){
      printf("Missing fragment shader\n");
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

	mPosHandle = glGetAttribLocation(mProgramID, "vPosition");
   if (mPosHandle == -1)
      printf("%s is not a valid shader program variable.\n","vPosition");

	mColorHandle = glGetUniformLocation(mProgramID, "fColor");
	if (mColorHandle == -1)
		printf("%s is not a valid shader program variable.\n","fColor");

	mProjHandle = glGetUniformLocation(mProgramID, "projMat");
   if (mProjHandle == -1)
      printf("%s is not a valid shader program variable.\n","projMat");

	mMVHandle = glGetUniformLocation(mProgramID, "MVMat");
   if (mMVHandle == -1)
      printf("%s is not a valid shader program variable.\n","MVMat");

	int DIM = 100;
	int th = 8;
	int PXA[DIM*DIM];
	for (int y=0; y<DIM; y++){
		for (int x=0; x<DIM; x++){
			if (x<th || x>DIM-th || y<th || y>DIM-th)
				PXA[y*DIM+x] = 0xFF000000;
			else
				PXA[y*DIM+x] = 0xFFFFFFFF;
		}
	}

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, DIM, DIM, 0, GL_RGBA, GL_UNSIGNED_BYTE, PXA);
	// Set filtering
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


	mTexCoordHandle = glGetAttribLocation(mProgramID, "a_TexCoord");
   if (mTexCoordHandle == -1)
      printf("%s is not a valid shader program variable.\n","a_TexCoord");

   mTexHandle = glGetUniformLocation(mProgramID, "u_Texture");
   if (mTexHandle == -1)
      printf("%s is not a valid shader program variable.\n","u_Texture");

	return true;
}

bool JShader::loadVert(std::string vertStr){
	mVS = loadShaderFromFile(vertStr,GL_VERTEX_SHADER);
   if (mVS == 0){
      printf("Invalid vertex shader.\n");
		return false;
	}
	return true;
}

GLint JShader::getPosHandle(){
	return mPosHandle;
}

GLuint JShader::getTexCoordHandle(){
	return mTexCoordHandle;
}

GLuint JShader::getTexHandle(){
	return texture;
}

void JShader::updateSampler(){
	glUniform1i(mTexHandle, 0);
}
bool JShader::loadFrag(std::string fragStr){
   mFS = loadShaderFromFile(fragStr,GL_FRAGMENT_SHADER);
   if (mFS == 0){
      printf("Invalid fragment shader.\n");
		return false;
	}
	return true;
}

void JShader::updateColor(GLfloat * color){
	glUniform4f(mColorHandle, color[0], color[1], color[2], color[3]);
}

void JShader::updateProj(GLfloat * proj){
   glUniformMatrix4fv(mProjHandle, 1, GL_FALSE, proj);
}

void JShader::updateMV(GLfloat * MV){
	glUniformMatrix4fv(mMVHandle, 1, GL_FALSE, MV);
}
