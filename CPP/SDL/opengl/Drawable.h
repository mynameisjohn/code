#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <GL/gl.h>

class Drawable{
	public:
		Drawable();
		~Drawable();
		void setMV(glm::mat4 newMatrix);
		void setColor(glm::vec4 newColor);
		void setColor(glm::vec3 newColor);
		void setColor(float r, float g, float b, float a=1.f);
		void setVBO(GLint VBO);
		void setIBO(GLint IBO);
		GLint getVBO();
		GLint getIBO();
		GLfloat * getMVPtr();
		GLfloat * getColorPtr();

	private:
		glm::mat4 MV;
		glm::vec4 color;
		GLuint mVBO, mIBO;
		GLfloat * vertices;
		int vertexCount;
};
