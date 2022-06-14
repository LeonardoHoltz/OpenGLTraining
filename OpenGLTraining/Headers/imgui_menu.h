// imgui_menu.h
#ifndef IMGUI_MENU_H
#define IMGUI_MENU_H

#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>

typedef struct {
	glm::vec4 triangle_color;
} ImguiMenuData;

class ImguiMenu {
public:
	ImguiMenuData menu_data;


	ImguiMenu(GLFWwindow* window);
	~ImguiMenu();

	void CreateFrame();
	void DefineFrameContent();

private:
	void DefineDefaultMenuData();
};

#endif IMGUI_MENU_H
