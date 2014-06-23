#include "circBuf.h"

class colBuf : public circBuf{
public:
	colBuf(int);
	void addDimCol(unsigned int, bool);
	bool handleIt(bool, bool, bool);
	bool collisionDetected();
private:
	int collisions;
	unsigned int x, y, z;
};


