#include "BoundBox.h"
#include "collisionBuf.h"
#include <iostream>

using namespace std;

int main(){
	BoundBox cube1(10, 20, 30, 40, 40, 40);
	BoundBox cube2(25, 260, 32, 40, 90, 40);
	colBuf colby(3);
	circBuf curc(3);

	bool colX = cube1.collidesX(cube2);
	bool colZ = cube1.collidesZ(cube2); 
	bool colY = cube1.collidesY(cube2);

	colby.handleIt(colX, colY, colZ);
	if (colby.collisionDetected())
		std::cout<< "Collision Detected" <<std::endl;
	else
		std::cout<< "No Collision" <<std::endl;
	
	cube2.translate(0, -220, 100);
	
	colX = cube1.collidesX(cube2);
   colZ = cube1.collidesZ(cube2);
   colY = cube1.collidesY(cube2);
	
	colby.handleIt(colX, colY, colZ);
	if (colby.collisionDetected())
      std::cout<< "Collision Detected" <<std::endl;
	else
      std::cout<< "No Collision" <<std::endl;

	cube2.translate(-100, 0, -100);

   colX = cube1.collidesX(cube2);
   colZ = cube1.collidesZ(cube2);
   colY = cube1.collidesY(cube2);

   colby.handleIt(colX, colY, colZ);
   if (colby.collisionDetected())
      std::cout<< "Collision Detected" <<std::endl;
   else
      std::cout<< "No Collision" <<std::endl;

	cube2.translate(100, 0, 0);

   colX = cube1.collidesX(cube2);
   colZ = cube1.collidesZ(cube2);
   colY = cube1.collidesY(cube2);

   colby.handleIt(colX, colY, colZ);
   if (colby.collisionDetected())
      std::cout<< "Collision Detected" <<std::endl;
   else
      std::cout<< "No Collision" <<std::endl;

   std::cout<< colby.last() <<std::endl;


	return 1;
}
