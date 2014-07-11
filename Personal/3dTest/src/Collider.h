#ifndef COLLIDER_H
#define COLLIDER_H

#ifndef GLM_FORCE_RADIANS 
#define GLM_FORCE_RADIANS 
#endif 
 
#include <glm/glm.hpp> 

#include <vector>
#include <map>
#include "BoundBox.h"
#include "iRect.h"
#include "ColBuf.h"

class Collider{
	public:
		Collider();
		~Collider();
		void setBB(BoundBox);
		void addSub(iRect sub);
		void setWalls(int, int, int, int, int, int);
		void clearSub();
		void translate(int, int, int);
		glm::vec3 move(glm::vec3 vel);
		bool collidesX(Collider&);
      bool collidesY(Collider&);
		bool collidesZ(Collider&);
      char collidesWith(Collider&);
		bool overlapsWith(Collider&);
	private:
		BoundBox mBB;
		std::vector<iRect> mSubs;
		int w_x, w_y, w_z, w_X, w_Y, w_Z;
		std::map<Collider *, ColBuf> cBufMap;
	public:
		inline int toLeft(Collider& c){
			return c.mBB.left()-mBB.right(); 
		}
		inline int toRight(Collider& c){
         return c.mBB.right()-mBB.left(); 
      }
		inline int toBottom(Collider& c){
         return c.mBB.bottom()-mBB.top(); 
      }
		inline int toTop(Collider& c){
         return c.mBB.top()-mBB.bottom(); 
      }
		inline int toNear(Collider& c){
			return c.mBB.near() - mBB.far();
		}
		inline int toFar(Collider& c){
         return c.mBB.near()-mBB.far(); 
      }
};

#endif
