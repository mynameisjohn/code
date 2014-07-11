#include "iCube.h"

class BoundBox : public iCube{
public:
	BoundBox();
   BoundBox(int x, int y, int z);
   BoundBox(int x, int y, int z, int w, int h, int d);
	void translate(int x, int y, int z);
	inline bool collidesWith(BoundBox& other);
	inline bool collidesX(BoundBox& other);
	inline bool collidesY(BoundBox& other);
	inline bool collidesZ(BoundBox& other);
};

inline bool BoundBox::collidesWith(BoundBox& other){
	return collidesX(other) && 
			 collidesY(other) && 
			 collidesZ(other);
}

inline bool BoundBox::collidesX(BoundBox& other){
	return !(right() < other.left() || left() > other.right());
}

inline bool BoundBox::collidesY(BoundBox& other){
	return !(bottom() < other.top() || top() > other.bottom());
}

inline bool BoundBox::collidesZ(BoundBox& other){
	return !(far() < other.near() || near() > other.far());
}
