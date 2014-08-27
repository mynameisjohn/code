#ifndef ENTITY_H
#define ENTITY_H

#include "Collider.h"

class Entity{
	public:
		Entity();
		Entity(Collider c);
		void setCol(Collider c);
		void setBB(BoundBox bb);
		void translate(vec3);
		virtual char collidesWith(Entity& e);
		bool overlapsWith(Entity& e);
		float toLeft(Entity&);	
		float toRight(Entity&);
		float toBottom(Entity&);
		float toTop(Entity&);
		float toNear(Entity&);
		float toFar(Entity&);
		vec3 getPos();
		vec3 center();
	protected:
		Collider mCollider;

	/* These will be inlined when the time comes
	public:
		inline void translate(vec3 trans){
			mCollider.translate(trans);
		}
		inline vec3 getPos(){
			return mCollider.getPos();
		}
		inline int toLeft(Entity& e){
			return mCollider.toLeft(e.mCollider);
		}
		inline int toRight(Entity& e){
         return mCollider.toRight(e.mCollider);
      }
		inline int toBottom(Entity& e){
         return mCollider.toBottom(e.mCollider);
      }
		inline int toTop(Entity& e){
         return mCollider.toTop(e.mCollider);
      }
		inline int toNear(Entity& e){
         return mCollider.toNear(e.mCollider);
      }
		inline int toFar(Entity& e){
         return mCollider.toFar(e.mCollider);
      }
		inline vec3 center(){
			return mCollider.center();
		}
*/
};


#endif
