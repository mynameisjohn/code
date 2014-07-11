#include "BoundBox.h"

BoundBox::BoundBox()
: iCube(){}

BoundBox::BoundBox(int W, int H, int D)
:iCube(W, H, D){}

BoundBox::BoundBox(int X, int Y, int Z, int W, int H, int D)
: iCube(X, Y, Z, W, H, D){}

void BoundBox::translate(int x, int y, int z){
	this->x+=x;
	this->y+=y;
	this->z+=z;
}
