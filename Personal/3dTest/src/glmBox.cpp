#include "glmBox.h"

glmBox::glmBox(){
	mPos=vec3();
	mDim=vec3(1, 1, 1);
}

glmBox::glmBox(vec3 dim){
	mPos=vec3();
	mDim=dim;
}

glmBox::glmBox(vec3 pos, vec3 dim){
	mPos=pos;
	mDim=dim;
}
