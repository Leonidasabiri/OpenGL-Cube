#include "Shaders.h"
#include "Textures.h"
#include "Cube.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void fbscallback(GLFWwindow *window, int width, int height);

const unsigned int WIDTH  = 800;
const unsigned int HEIGHT = 800;


int main()
{
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT,"BSP",NULL,NULL);
	glfwMakeContextCurrent(window);
	glfwSetWindowSizeCallback(window, fbscallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return -1;
	
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	ImGui::StyleColorsClassic();

	Shader shader;
	shader.parseShaderCode("Vertex.shader", "Fragement.shader");

	Cube cube, cube1;
	cube.initCube();
	cube1.initCube();

	Texture tex;
	tex.applyTexture("resources/dark.png");	
	
	while (!glfwWindowShouldClose(window))
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		tex.bindTexture();	

		static float fov	  = 45.0f;
		static float scale_factor = 1.0f;
		static float rotationx	  = 0.0f;
		static float x = 0.0f, y  = 0.0f , scaleX = 0.0f, scaleY = 0.0f;
		static float color[3]	  = { 1.0f,1.0f,1.0f};
		
		cube.renderCube(shader.getShderProgramID(), rotationx, fov, 0.1f, WIDTH, HEIGHT);
		cube1.renderCube(shader.getShderProgramID(), rotationx, fov, 0.4f, WIDTH, HEIGHT);
		ImGui::Begin("Transform");
		ImGui::SliderFloat("Rotation :", &rotationx, -100.0, 100.0f);
		ImGui::SliderFloat("FOV  :", &fov, -500.0f, 500.0f);
		ImGui::SliderFloat("Scale:", &scale_factor, -500.0f, 500.0f);
		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	cube.destroyCube();
	glfwTerminate();
}

void fbscallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
