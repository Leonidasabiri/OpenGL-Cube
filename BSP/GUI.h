#ifndef GUI_H
 #define GUI_H
 #include "imgui/imgui.h"
 #include "imgui/imgui_impl_glfw.h"
 #include "imgui/imgui_impl_opengl3.h"

class GUI
{
public:
	void initIMGUI(GLFWwindow* window);	
	void newFrame();
	template<typename T>
	void transformsGUI(T rotationx, T fov);
};

#endif