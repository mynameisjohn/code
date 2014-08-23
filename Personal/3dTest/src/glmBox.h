#ifndef GLM_BOX
#define GLM_BOX

#ifndef GLM_FORCE_RADIANS 
#define GLM_FORCE_RADIANS 
#endif

#include <glm/glm.hpp>
#include <iostream>

using glm::vec3;

class glmBox{
	public:
		glmBox();
		glmBox(vec3 dim);
		glmBox(vec3 pos, vec3 dim);
	protected:
		vec3 mPos;
		vec3 mDim;
//inline functions 
public: 
   inline float left(){ 
      return mPos.x; 
   } 
 
   inline float right(){ 
      return mPos.x+mDim.x;
   }

   inline float bottom(){
      return mPos.y+mDim.y;
   }

   inline float top(){
      return mPos.y;
   }

   inline float near(){
      return mPos.z;
   }

   inline float far(){
      return mPos.z+mDim.z;
   }

	inline vec3 getPos(){
		return mPos;
	}

	inline vec3 getDim(){
		return mDim;
	}
	inline vec3 center(){
		return mPos + mDim/2.f;
	}
};

#endif
