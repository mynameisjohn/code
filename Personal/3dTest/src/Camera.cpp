#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

Camera::Camera(){
	buf=100.f; 
	projMat=glm::perspective((float)M_PI/4.f, 4.f/3, 100.f, 4000.f);
	projMat = glm::scale(glm::vec3(1.f, -1.f, -1.f)) * projMat;//remove this
}

Camera::Camera(float b, mat4 p){
	buf = b;
	projMat=p;
}

void Camera::translate(vec3 trans){
	mBB.translate(trans);
	projMat = glm::translate(trans) * projMat;
}

//what a strange method...
void Camera::push(vec3 center){
	float dX;

	dX = center.x-mBB.left();	
	if (dX < buf){//don't sweat the small stuff...
		translate(vec3(dX, 0, 0));
		return;
	}

	dX = mBB.right() - center.x;
	if (dX < buf){
		translate(vec3(dX, 0, 0));
	}

	return;
}

void Camera::setProjMat(mat4 p){
	projMat = p;
}

void Camera::leftMultProjMat(mat4 m){
	projMat = m*projMat;
}

mat4 Camera::getProjMat(){
	return projMat;
}
