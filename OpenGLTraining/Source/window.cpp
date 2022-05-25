#include "../Headers/window.h"
#include <iostream>

Window::Window() {
	
	if (glfwInit() == GLFW_FALSE)
		throw std::runtime_error("Could not init GLFW");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window_ = glfwCreateWindow(1280, 720, "OpenGL training", nullptr, nullptr);
	if (window_ == nullptr)
	{
		glfwTerminate();
		throw std::runtime_error("Failed to create GLFW window");
	}
	glfwMakeContextCurrent(window_);
}

Window::~Window() {
	glfwTerminate();
}