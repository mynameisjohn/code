#ifndef IRECT_H
#define IRECT_H
/*
class iRect{
	public:
		iRect();
		~iRect();
		bool vCollision(iRect * other);
		bool hCollision(iRect * other);
		bool checkCollision(iRect * other);
	private:
		int x, y;
		int w, h;
};
*/

typedef struct iRect{
	int x; int y;
	int w; int h;
} iRect;

int bottom(iRect rect);
int top(iRect rect);
int right(iRect rect);
int left(iRect rect);
bool vCollision(iRect A, iRect B);
bool hCollision(iRect A, iRect B);
bool checkCollision(iRect A, iRect B);


/*
int bottom(iRect rect){
	return rect.y+rect.h;
}

int top(iRect rect){
	return rect.y;
}

int right(iRect rect){
	return rect.x+rect.w;
}

int left(iRect rect){
	return rect.x;
}

bool vCollision(iRect A, iRect B){
	return !(bottom(A) <= top(B) || top(A) >= bottom(B));
}

bool hCollision(iRect A, iRect B){
   return !(right(A) <= left(B) || left(A) >= right(B));
}

bool checkCollision(iRect A, iRect B){
   return (vCollision(A,B) && hCollision(A,B));
}
*/
#endif
