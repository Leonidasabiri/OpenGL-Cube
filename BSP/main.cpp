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

	unsigned int VBO, VAO, EBO;
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	
	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indecies), indecies, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	unsigned int transformloc = glGetUniformLocation(shader.getShderProgramID(), "transform");
	unsigned int uniff		  = glGetUniformLocation(shader.getShderProgramID(), "color");

	Texture tex;
	tex.applyTexture("resources/dark.png");	
	
	while (!glfwWindowShouldClose(window))
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		glClearColor(0.2f, 1.0f, 0.4f, 0.2f);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		static float fov		  = 45.0f;
		static float scale_factor = 1.0f;
		static float rotationx	  = 0.0f;
		static float x = 0.0f, y  = 0.0f , scaleX = 0.0f, scaleY = 0.0f;
		static float color[3]	  = { 1.0f,1.0f,1.0f};

		tex.bindTexture();

		glm::mat4 model			= glm::mat4(1.0f);
		glm::mat4 view			= glm::mat4(1.0f);
		glm::mat4 projection	= glm::mat4(1.0f);

		model = glm::rotate(model, glm::radians(rotationx), glm::vec3(1.0f, 0.0f, 0.0f));
		view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		projection = glm::perspective(glm::radians(fov), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
		//trans = glm::scale(trans, glm::vec3(scaleX, scaleY, 1.0f));

		int modelloc = glGetUniformLocation(shader.getShderProgramID(), "model");
		int viewloc  = glGetUniformLocation(shader.getShderProgramID(), "view");
		int projloc  = glGetUniformLocation(shader.getShderProgramID(), "projection");

		// Changing uniforms
		//glUniform3fv(uniff, 1, color);
		glUniformMatrix4fv(modelloc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewloc, 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(projloc, 1, GL_FALSE, &projection[0][0]);

		glUseProgram(shader.getShderProgramID());
	//	glUniformMatrix4fv(transformloc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		ImGui::Begin("Transforms");
		ImGui::SliderFloat("Rotation :", &rotationx, -100.0, 100.0f);
		ImGui::SliderFloat("FOV  :",   &fov, -500.0f, 500.0f);
		ImGui::SliderFloat("Coord Y  :", &y, -10.0, 10.0f);
		ImGui::ColorEdit3("Color", color);
		ImGui::End();
		// Render dear imgui into screen
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	glfwTerminate();
}

void fbscallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
