#ifndef CUBE_H
 #define CUBE_H
 #include <glad/glad.h>
 #include <glfw/glfw3.h>
 #include <glm/glm.hpp>
 #include <glm/gtc/matrix_transform.hpp>
 #include <glm/gtc/type_ptr.hpp>

class Cube
{
	int shaderID;
public:
	void  initCube();
	void  renderCube(int shaderID, float rotation, float fov, float x, int WIDTH, int HEIGHT);
	void  destroyCube();
};

#endif