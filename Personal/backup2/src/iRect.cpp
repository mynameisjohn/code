#include "iRect.h"

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

