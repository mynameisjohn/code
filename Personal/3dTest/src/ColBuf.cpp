#include "ColBuf.h"

colBuf::colBuf(int dim)
: circBuf(dim)
{
	this->dim=dim;
	collisions=0;
	x=1; y=2; z=4;
}

void colBuf::addDimCol(unsigned int eig, bool col){
	if (col){ //if this dimension has collided
      if (~collisions & eig){ //if it's not already in the bit vector
         add(eig); //add it to the buffer
         collisions |= eig; //then or the bit
      }
   }//otherwise, remove the dimension from the bit vector
	else collisions &= ~eig;

	return;
}

bool colBuf::handleIt(bool colX, bool colY, bool colZ){
	addDimCol(x, colX);
	addDimCol(y, colY);
	addDimCol(z, colZ);

	return collisionDetected();
}

bool colBuf::collisionDetected(){
	return collisions == (x|y|z);
}
