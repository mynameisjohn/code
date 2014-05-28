#include "Drawable.h"

class Player : public Drawable{
	public:
		void handleEvent();
		void setX();
	private:
		int x;
};
