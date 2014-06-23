#ifndef COLLIDER_H
#define COLLIDER_H

#ifndef GLM_FORCE_RADIANS 
#define GLM_FORCE_RADIANS 
#endif 
 
#include <glm/glm.hpp> 

#include <vector>
#include "BoundBox.h"
#include "iRect.h"

class Collider{
	public:
		Collider();
		void setBB(BoundBox);
		void addSub(iRect sub);
		void setWalls(int, int, int, int, int, int);
		void clearSub();
		void translate(int, int, int);
		glm::vec3 move(glm::vec3 vel);
		bool collidesX(Collider&);
      bool collidesY(Collider&);
		bool collidesZ(Collider&);
      bool collidesWith(Collider&);
		bool overlapsWith(Collider&);
	private:
		BoundBox mBB;
		std::vector<iRect> mSubs;
		int w_x, w_y, w_z, w_X, w_Y, w_Z;	
};

#endif
