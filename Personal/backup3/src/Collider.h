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
		void moveTo(int x, int y);
		bool overlaps_X(Collider& other);
		bool overlaps_Y(Collider& other);
		bool collidesWith(Collider& other);
		void move(int velX, int velY, int& oldX, int& oldY);
		glm::vec3 diff(int oldX, int oldY);
		int getTopTop();
		int getTopBottom();
		int getTopRight();
		int getTopLeft();
		int getTop_h();
		int getTop_w();
	private:
		iRect mTop;
		std::vector<iRect> mSub;
		int wall_x, wall_y, wall_X, wall_Y;
};

#endif
