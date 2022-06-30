#ifndef APPLICATION_H
#define APPLCIATION_H

// C++
#include <iostream>
#include <stdlib.h>
#include <vector>

// OpenGL
#include <glad/glad.h>

// Custom
#include "camera.h"
#include "window.h"
#include "callbacks.h"
#include "shader.h"
#include "imgui_menu.h"
#include "model.h"


class Application {
private:

	struct ShaderUniformData {
		// Matrices
		glm::mat4 view_matrix;
		glm::mat4 projection_matrix;
		glm::mat4 model_matrix;

		// Light
		glm::vec3 light_position;
		glm::vec3 light_intensity;
		int shininess;
	};

	Window window;
	Camera camera;
	ImguiMenu menu;
	Callbacks* callbacks;

	std::vector<Shader> shaders;
	ShaderUniformData shader_data;
	std::vector<Model> models_loaded;

	enum AttributePointers { vModelMatrix = 3, vViewMatrix = 4, vProjectionMatrix = 5, fLightIntensity = 6, fShininess = 7, fLightPosition = 8 };

	void InitGlad();
	void MainLoop();
	void ClearScreen(glm::vec4 clear_color);
	void LoadScene();
	void DrawScene(Shader shader);
	void DefineShaders();
	void CheckForInputs();
	void SetTransformationMatrices();
	void ApplyMenuOptions();
	void SetUniformValues();

public:
	Application();
	~Application();

	int Run();
};

#endif // !APPLICATION_H
