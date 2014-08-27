#ifndef COLLIDER_H
#define COLLIDER_H

#include <vector>
#include <map>
#include "BoundBox.h"
#include "iRect.h"
#include "ColBuf.h"

class Collider{
	public:
		Collider();
		Collider(vec3 w_min, vec3 w_max, BoundBox bb);
		~Collider();
		void setBB(BoundBox);
		void addSub(iRect sub);
		void setWalls(vec3 min, vec3 max);
		void clearSub();
		void translate(vec3 trans);
		bool move(vec3 vel);
		bool collidesX(Collider&);
      bool collidesY(Collider&);
		bool collidesZ(Collider&);
      char collidesWith(Collider&);
		bool overlapsWith(Collider&);
		float toLeft(Collider& c);
		float toRight(Collider& c);
		float toBottom(Collider& c);
		float toTop(Collider& c);
		float toNear(Collider& c);
		float toFar(Collider& c);
		vec3 getPos();
		vec3 center();
	private:
		BoundBox mBB;
		std::vector<iRect> mSubs;
		vec3 W_min, W_max;
		std::map<Collider *, ColBuf> cBufMap;
	public:
		/* 
			I'll re-inline these when the time comes
		inline vec3 getPos(){
			return mBB.getPos();
		}
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
		inline vec3 center(){
			return mBB.center();
		}
		*/
};

#endif
