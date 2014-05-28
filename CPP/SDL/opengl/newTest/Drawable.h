#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <GL/gl.h>

#include <SDL2/SDL.h>

#include <vector>

typedef struct collider{
	SDL_Rect top;
	std::vector<SDL_Rect> sub;
} collider;

class Drawable{
	public:
		Drawable();                         //Default Constructor
		~Drawable();                        //Default Destructor
		void initGeom();                    //Initialize Geometry
		void setMV(glm::mat4 newMatrix);    //set MV matrix
		void setColor(glm::vec4 newColor);  //set color
		void setColor(glm::vec3 newColor);  //set color
		void setColor(float r, float g, float b, float a=1.f); //set color
		void setVBO(GLint VBO);             //set VBO handle
		void setIBO(GLint IBO);             //set IBO handle
		GLint getVBO();                     //return VBO handle
		GLint getIBO();                     //return IBO handle
		GLfloat * getMVPtr();               //get pointer to MV matrix
		GLfloat * getColorPtr();            //get pointer to Color
		void leftMultMV(glm::mat4 left);    //multiply matrix by something
	private:
		glm::mat4 MV;            //Model View Matrix
		glm::vec4 color;         //Color
		GLuint mVBO, mIBO;       //Vertex/Index Buffer Object Handles
		GLfloat * vertices;      //Vertices (needed?)
		int vertexCount;         //Vertex Count (probably needed)
		collider mCollider;      //Collision Rectangles
};
