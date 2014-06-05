#ifndef COLLIDER_H
#define COLLIDER_H

#include <glm/glm.hpp>
#include <vector>
#include "iRect.h"

class Collider{
	public:
		Collider();
		~Collider();
		void setTop(iRect top);
		void addSub(iRect sub);
		void setWalls(int x, int y, int X, int Y);
		void clearSub();
		bool collidesWith(Collider * other);
		glm::vec3 move(int velX, int velY);
	private:
		iRect mTop;
		std::vector<iRect> mSub;
		int wall_x, wall_y, wall_X, wall_Y;
};

#endif
