// OpenGLTraining.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <stdlib.h>

#include <glad/glad.h>

#include "Headers/window.h"
#include "Headers/callbacks.h"

void InitGlad(Window& window);
void MainLoop(Window& window);

int main()
{
	try {
		Window window = Window();
		InitGlad(window);
		MainLoop(window);
		window.~Window();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

    return EXIT_SUCCESS;
}

void InitGlad(Window& window) {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		throw std::runtime_error("Failed to initialize GLAD");
	}
	glViewport(0, 0, 1280, 720);
	glfwSetFramebufferSizeCallback(window.window_, Callbacks::framebuffer_size_callback);
}

void MainLoop(Window& window) {

	while (!glfwWindowShouldClose(window.window_))
	{
		glfwSwapBuffers(window.window_);
		glfwPollEvents();
	}
}