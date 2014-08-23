#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

Camera::Camera(){
	buf=200.f; 
	mBB = BoundBox(vec3(-1000,0,0),vec3(2000,0,0));
	projMat=glm::perspective((float)M_PI/4.f, 4.f/3, 100.f, 10000.f);
	projMat =  
glm::scale(glm::vec3(1.f, -1.f, -1.f)) * projMat * 
glm::rotate((float)-M_PI/15.f, vec3(1, 0, 0)) * 
glm::translate(vec3(0, 750, 0));//remove this
}

Camera::Camera(float b, mat4 p){
	buf = b;
	projMat=p;
}

void Camera::translate(vec3 trans){
	mBB.translate(-trans);
	projMat = projMat * glm::translate(trans);
}

//what a strange method...
void Camera::push(vec3 center){
	float dX;

	dX = (center.x-mBB.left());
	//printf("%lf\t",dX);	
	if (dX < buf){//don't sweat the small stuff...
		translate(vec3(40.f, 0, 0));
		return;
	}

	dX = (mBB.right() - center.x);
	//printf("%lf\n",dX);	
	if (dX < buf){
		translate(vec3(-40.f, 0, 0));
	}

	return;
}

void Camera::setProjMat(mat4 p){
	projMat = p;
}

void Camera::leftMult(mat4 m){
	projMat = m * projMat;
}

void Camera::rightMult(mat4 m){
	projMat = projMat * m;
}

mat4 Camera::getProjMat(){
	return projMat;
}
