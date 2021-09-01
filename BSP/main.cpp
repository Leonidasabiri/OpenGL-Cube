#include "Shaders.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//#include <iostream>

int main()
{
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(600,600,"BSP",NULL,NULL);
	glfwMakeContextCurrent(window);

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

	float vertices[] =
	{
		 0.0f,   0.1f, 0.0f,
		-0.1f,  -0.1f, 0.0f,
		 0.1f,  -0.1f, 0.0f
	};


	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(VAO);

	unsigned int transx = glGetUniformLocation(shader.getShderProgramID(), "transx");
	unsigned int transy = glGetUniformLocation(shader.getShderProgramID(), "transy");
	unsigned int uniff = glGetUniformLocation(shader.getShderProgramID(), "color");

	while (!glfwWindowShouldClose(window))
	{
		// feed inputs to dear imgui, start new frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		glClearColor(0.2f, 1.0f, 0.4f, 0.2f);
		glClear(GL_COLOR_BUFFER_BIT);

		static float scale_factor = 0.0f;
		static float x = 0.0f, y = 0.0f , scaleX = 0.0f, scaleY = 0.0f;
		static float color[3] = { 1.0f,1.0f,1.0f};

		glUniform1f(transx, x);
		glUniform1f(transy, y);
		glUniform3fv(uniff, 1, color);

		glUseProgram(shader.getShderProgramID());
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		ImGui::Begin("Transforms");
		ImGui::SliderFloat("Coord X:", &x, 0.0f, 10.0f);
		ImGui::SliderFloat("Scale: ", &scale_factor, 0.0f, 10.0f);
		ImGui::SliderFloat("Coord Y:", &y, 0.0f, 10.0f);
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

