#include "Drawable.h"

void printRect(SDL_Rect rect){
	printf("%lf, %lf\n", rect.x, rect.y);
}

Drawable::Drawable(){
	MV = glm::mat4();
	color = glm::vec4(1.f,1.f,1.f,1.f);
	mVBO = -1;
	mIBO = -1;
	speed = 10;
	mVelX = 0;
	mVelY = 0;
	visible = true;
	xFirst = false;
}

Drawable::~Drawable(){
	mVBO = -1;
	mIBO = -1;
}

void Drawable::update(){
	//none for now
}

void Drawable::initGeom(){
/*	//VBO data
   GLfloat vertexData[] =
   {
      -50.f, -50.f,
       50.f, -50.f,
       50.f,  50.f,
      -50.f,  50.f
   };

   //IBO data
   GLuint indexData[] = { 0, 1, 2, 3 };

	//Create VBO
   glGenBuffers( 1, &mVBO );
   glBindBuffer( GL_ARRAY_BUFFER, mVBO );
   glBufferData( GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW );
*/
}

void Drawable::setMV(glm::mat4 newMV){
	MV = newMV;
}

void Drawable::setColor(glm::vec4 newColor){
	color = newColor;
}

void Drawable::setColor(glm::vec3 newColor){
	color = glm::vec4(newColor,1.f);
}

void Drawable::setColor(float r, float g, float b, float a){
	color = glm::vec4(r, g, b, a);
}

void Drawable::setVBO(GLint VBO){
	mVBO = VBO;
}

void Drawable::setIBO(GLint IBO){
	mIBO = IBO;
}

GLint Drawable::getVBO(){
	return mVBO;
}

GLint Drawable::getIBO(){
	return mIBO;
}

GLfloat * Drawable::getMVPtr(){
	return glm::value_ptr(MV);
}

GLfloat * Drawable::getColorPtr(){
	return glm::value_ptr(color);
}

void Drawable::leftMultMV(glm::mat4 left){
	MV = left * MV;
}

void Drawable::setTop(SDL_Rect top){
	mTopCol=top;
}

void Drawable::addSub(SDL_Rect sub){
	mSubCols.push_back(sub);
}
/*
void Drawable::handleEvent(SDL_Event& e){
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
		switch(e.key.keysym.sym){
			case SDLK_UP: mVelY -= speed; break;
         case SDLK_DOWN: mVelY += speed; break;
         case SDLK_LEFT: mVelX -= speed; break;
         case SDLK_RIGHT: mVelX += speed; break;
		}
   }
	else if ( e.type == SDL_KEYUP && e.key.repeat == 0 ){
      switch(e.key.keysym.sym){
         case SDLK_UP: mVelY += speed; break;
         case SDLK_DOWN: mVelY -= speed; break;
         case SDLK_LEFT: mVelX += speed; break;
         case SDLK_RIGHT: mVelX -= speed; break;
      }
   }
}
*/

bool checkVCollision( SDL_Rect * a, SDL_Rect * b )
{
    //The sides of the rectangles
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    topA = a->y;
    bottomA = a->y + a->h;

    //Calculate the sides of rect B
    topB = b->y;
    bottomB = b->y + b->h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    return true;
}

bool checkHCollision(SDL_Rect * a, SDL_Rect * b){
   //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;

    //Calculate the sides of rect A
    leftA = a->x;
    rightA = a->x + a->w;

    //Calculate the sides of rect B
    leftB = b->x;
    rightB = b->x + b->w;

   if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

void Drawable::move(int x, int y, int X, int Y, SDL_Rect * other){
	glm::vec3 translate = glm::vec3();
	int oldX = mTopCol.x; int oldY = mTopCol.y;	

	if (mTopCol.x + mVelX < x){
		//translate.x = mTopCol.x;
		mTopCol.x = x;
	}
	else if (mTopCol.x + mTopCol.w + mVelX > X){
      //translate.x = mTopCol.x + mTopCol.w-X;
      mTopCol.x = X - mTopCol.w;
   }
	else{
		mTopCol.x += mVelX;
		//translate.x = mVelX;
	}
	if (mTopCol.y + mVelY < y){
      //translate.y = mTopCol.y;
      mTopCol.y = y;
   }
   else if (mTopCol.y +mTopCol.h + mVelY > Y){
      //translate.y = mTopCol.y + mTopCol.h - Y;
      mTopCol.y = Y - mTopCol.h;
   }
   else{
      mTopCol.y += mVelY;
      //translate.y = mVelY;
   }

	bool colX, colY;
   colX=checkHCollision(&mTopCol,other);
   colY=checkVCollision(&mTopCol,other);

   if (colX && colY){
      if (xFirst){
         if (mVelY<0){
            //translate.y = other->y+other->h-mTopCol.y;
				mTopCol.y = other->y+other->h;
			}
         else if (mVelY>0){
            //translate.y = other->y-(mTopCol.y+mTopCol.h);
				mTopCol.y = other->y - mTopCol.h;
			}
      }
      else {
			if (mVelX<0){
            //translate.x = other->x+other->w-mTopCol.x;
            mTopCol.x = other->x+other->w;
         }
         else if (mVelX>0){
            //translate.x = other->x-(mTopCol.x+mTopCol.w);
            mTopCol.x = other->x - mTopCol.w;
         }
		}
		//printRect(mTopCol);
   }
	else
		xFirst = colX && !colY;

	translate.x = mTopCol.x - oldX;
	translate.y = mTopCol.y - oldY;

	std::vector<SDL_Rect>::iterator rectIter;
	for (rectIter=mSubCols.begin(); rectIter != mSubCols.end(); rectIter++){
		rectIter->x += mVelX; rectIter->y += mVelY;
	}

	leftMultMV(glm::translate(translate));
}

bool Drawable::drawMe(){
	return visible;
}

SDL_Rect * Drawable::getTopColPtr(){
	return &mTopCol;
}

void Drawable::translate(float x, float y, float z){
	glm::vec3 translate;
	translate.x=x;
	translate.y=y;
	translate.z=z;
	leftMultMV(glm::translate(translate));
}
