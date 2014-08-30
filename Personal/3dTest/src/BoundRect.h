#ifndef BOUND_RECT
#define BOUND_RECT

#include "glmRect.h"

class BoundRect : public glmRect{
public:
	BoundRect();
	BoundRect(vec2 dim);
	BoundRect(vec2 pos, vec2 dim);
	void translate(vec2 trans);
	bool collidesWith(BoundRect other);//Doesn't seem worth passing by reference
	bool collidesX(BoundRect other); //but do inline eventually
	bool collidesY(BoundRect other);
};

#endif
