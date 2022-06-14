// OpenGLTraining.cpp

// C++
#include <iostream>
#include <stdlib.h>

// OpenGL
#include <glad/glad.h>

// Project headers
#include "Headers/window.h"
#include "Headers/imgui_menu.h"
#include "Headers/rendering.h"

// Assimp
#include <assimp/Importer.hpp>		// C++ importer interface
#include <assimp/scene.h>			// Output data structure
#include <assimp/postprocess.h>		// Post processing flags

void InitGlad(Window& window);
void MainLoop(Window& window, ImguiMenu& menu, Rendering& render);

int main()
{
	try {
		Window window;
		InitGlad(window);
		ImguiMenu menu(window.window_);
		Rendering render(window);
		render.PrepareDataForRendering();
		render.DefineTexture(menu.menu_data);
		render.DefineCallbacks();
		MainLoop(window, menu, render);
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
}

void MainLoop(Window& window, ImguiMenu& menu, Rendering& render) {

	while (!glfwWindowShouldClose(window.window_))
	{
		render.ClearScreen(CLEAR_COLOR_BLACK);

		menu.CreateFrame();

		// Main Logic
		render.BindMainObjectVertexArray();
		render.BindMainObjectTexture();
		render.SetUniformValues(menu.menu_data);
		render.SetTransformationMatrices();
		render.CalculateFramerate();
		render.CheckForInputs();
		glDrawArrays(GL_TRIANGLES, 0, 6);

		menu.DefineFrameContent();

		glfwSwapBuffers(window.window_);
		glfwPollEvents();
	}
}