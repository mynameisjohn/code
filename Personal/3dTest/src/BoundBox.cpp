#include "BoundBox.h"
#include <stdio.h>

BoundBox::BoundBox()
: glmBox(){}

BoundBox::BoundBox(vec3 dim)
:glmBox(dim){}

BoundBox::BoundBox(vec3 pos, vec3 dim)
: glmBox(pos, dim){}

void BoundBox::translate(vec3 trans){
	mPos += trans;
}
