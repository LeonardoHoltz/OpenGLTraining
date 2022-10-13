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

	struct SubroutinesIndices {
		// Light Modifications:
		GLuint applyAttenuationIndex;
		GLuint dontAddModificationsIndex;
	};

	struct ShaderUniformData {
		// Subroutines
		SubroutinesIndices subroutineIndices;

		// Matrices
		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
		glm::mat4 modelMatrix;

		// Light
		glm::vec3 lightPosition;
		glm::vec3 lightIntensity;
		int shininess;
		bool IsLightAttenuationOn;
	};

	Window window;
	Camera camera;
	ImguiMenu menu;
	Callbacks* callbacks;

	std::vector<Shader> shaders;
	ShaderUniformData shaderData;
	std::vector<Model> modelsLoaded;

	// v prefixes for attribute pointers used in the vertex shader, f for the ones used in the fragment shader
	enum AttributePointers { v_eModelMatrix = 3, v_eViewMatrix = 4, v_eProjectionMatrix = 5, f_eLightIntensity = 6, f_eShininess = 7, f_eLightPosition = 8,
							 f_eIsLightAttetuationOn = 9 };

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
	void SetupSubroutines();

public:
	Application();
	~Application();

	int Run();
};

#endif // !APPLICATION_H
