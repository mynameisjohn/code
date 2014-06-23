#include "LevelManager.h"

#define SPACE_WIDTH 400
#define SPACE_HEIGHT 300

bool initLevel(std::vector<Drawable>& drawables, std::vector<Entity>& entities, int vHandle, int tHandle){
	const int nPlayer = 1;
   const int nNPC = 2;
   const int nScenery = 1;
   const int nDrawables = nPlayer+nNPC+nScenery;
	Player * playerPtr;

   drawables.clear();
   drawables.resize(nDrawables);

   //I REALIZE THE BEST SOLUTION WOULD BE TO WRITE A FUNCTION
   //THAT CREATES DRAWABLES AND ENTITIES TOGETHER. IT WAS
   //BUGGY AS FUCK, SO I GAVE UP. WOULD LOVE TO FIX IT. 
   Entity tri1_e, tri2_e;
   Player square_e;
   Collider rect_sc;

   //scenery.push_back(rect_sc);

   std::vector<bool> xFirst;
   xFirst.push_back(false);
   tri1_e.setXFirst(xFirst);
   tri2_e.setXFirst(xFirst);
   square_e.setXFirst(xFirst);

   tri1_e.setWalls(0, 0, SPACE_WIDTH, SPACE_HEIGHT);
   tri2_e.setWalls(0, 0, SPACE_WIDTH, SPACE_HEIGHT);
   square_e.setWalls(0, 0, SPACE_WIDTH, SPACE_HEIGHT);

   entities.push_back(tri1_e);
   entities.push_back(tri2_e);
   entities.push_back(square_e);

   //drawables[0].setCollider(&scenery[0]);
   drawables[1].setEntity(&entities[0]);
   drawables[2].setEntity(&entities[1]);
   drawables[3].setEntity(&entities[2]);

   playerPtr = (Player *)(&entities.back());
   //NOW INITGEOM STARTS

   if (!initSquare(&drawables[3], 3*SPACE_WIDTH/4, SPACE_HEIGHT/2, vHandle, tHandle)){
      printf("Error initializing geometry.\n");
      return false;
   }

   if (!initSquare(&drawables[2], 50, SPACE_HEIGHT/2, vHandle, tHandle)){
      printf("Error initializing geometry.\n");
      return false;
   }
/*
   if (!initSquare(&drawables[1], 50, 50, shader)){
      printf("Error initializing geometry.\n");
      return false;
   }

   if (!initSquare(&drawables[0], 250, SPACE_HEIGHT/2, shader)){
      printf("Error initializing geometry.\n");
      return false;
   }
*/
   return true;
}
