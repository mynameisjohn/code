#include "circBuf.h"

class colBuf : public circBuf{
public:
	colBuf(int dim = 3);
	void addDimCol(unsigned int, bool);
	bool handleIt(bool, bool, bool);
	bool collisionDetected();
private:
	int collisions;
	unsigned int x, y, z;
};


