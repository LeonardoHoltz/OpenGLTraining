// imgui_menu.h
#ifndef IMGUI_MENU_H
#define IMGUI_MENU_H

#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

enum RenderModes {Points = 0, Wireframe = 1, Solid = 2};

typedef struct {
	int render_mode;

	// Light
	glm::vec3 light_pos;
	glm::vec3 light_intensity;
	int shininess;
} ImguiMenuData;

class ImguiMenu {
public:
	ImguiMenuData menu_data;

	ImguiMenu(GLFWwindow* window);
	~ImguiMenu();

	void CreateFrame();
	void DefineFrameContent(float fps);

private:
	void DefineDefaultMenuData();
	void RenderingModeContent();
	void LightningContent();
};

#endif IMGUI_MENU_H
