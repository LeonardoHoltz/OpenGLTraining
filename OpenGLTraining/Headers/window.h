// window.h
#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>

class Window {
public:
	GLFWwindow* window_;
	
	Window();
	~Window();
	void TerminateWindow();
};

#endif // WINDOW_H