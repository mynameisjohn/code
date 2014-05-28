#include "Drawable.h"
#include <cmath>

class NPC : public Drawable{
	public:
		NPC();
		void handleEvent(SDL_Event& e);
		void update();
	private:
		float theta, dTheta, A;
};
