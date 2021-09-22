#include "GUI.h"

void GUI::initIMGUI(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	ImGui::StyleColorsClassic();
}

void GUI::newFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

template<typename T>
void GUI::transformsGUI(T rotationx,T fov)
{
	ImGui::Begin("Transforms");
	ImGui::SliderFloat("Rotation :", &rotationx, -100.0, 100.0f);
	ImGui::SliderFloat("FOV  :", &fov, -500.0f, 500.0f);
	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}