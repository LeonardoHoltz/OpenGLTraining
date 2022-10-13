#include "../Headers/Application.h"

#include <glm/gtc/type_ptr.hpp>

#define CLEAR_COLOR_BLACK glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)

Application::Application() : menu(window.window_) {

}

Application::~Application() {

}

int Application::Run() {
	try {
		InitGlad();

		glEnable(GL_DEPTH_TEST); // Dont EVER forget this line again...
		glFrontFace(GL_CCW);

		// Backface culling
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		DefineShaders();
		LoadScene();
		callbacks = new Callbacks(window, camera);
		SetupSubroutines();

		MainLoop();
		window.TerminateWindow();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

void Application::InitGlad() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		throw std::runtime_error("Failed to initialize GLAD");
	}
	glViewport(0, 0, 1280, 720);
}

void Application::ClearScreen(glm::vec4 clear_color) {
	glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Application::DefineShaders() {
	// For now, we'll use just one shader
	Shader shader;
	shader.SetupShaders("./Source/Shaders/simple_phong.vert", "./Source/Shaders/simple_phong.frag");
	shaders.push_back(shader);
}

void Application::LoadScene() {
	Model model("./Models/backpack/backpack.obj");
	modelsLoaded.push_back(model);
}

void Application::DrawScene(Shader shader) {
	for (Model & model : modelsLoaded) {
		model.Draw(shader);
	}
}

void Application::MainLoop() {
	while (!glfwWindowShouldClose(window.window_))
	{
		ClearScreen(CLEAR_COLOR_BLACK);

		menu.CreateFrame();

		CheckForInputs();
		SetUniformValues();
		camera.CalculateFrameRate();

		ApplyMenuOptions();

		DrawScene(shaders[0]);

		menu.DefineFrameContent(camera.fps);

		glfwSwapBuffers(window.window_);
		glfwPollEvents();
	}
}

void Application::CheckForInputs() {
	// Camera Translation:
	if (glfwGetKey(window.window_, GLFW_KEY_D) == GLFW_PRESS)
		camera.MoveCameraToRight();
	if (glfwGetKey(window.window_, GLFW_KEY_A) == GLFW_PRESS)
		camera.MoveCameraToLeft();
	if (glfwGetKey(window.window_, GLFW_KEY_W) == GLFW_PRESS)
		camera.MoveCameraForwards();
	if (glfwGetKey(window.window_, GLFW_KEY_S) == GLFW_PRESS)
		camera.MoveCameraBackwards();
	if (glfwGetKey(window.window_, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera.MoveCameraUpwards();
	if (glfwGetKey(window.window_, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		camera.MoveCameraDownwards();

	// Camera Rotation:
	if (glfwGetKey(window.window_, GLFW_KEY_Q) == GLFW_PRESS)
		camera.TiltCameraLeft();
	if (glfwGetKey(window.window_, GLFW_KEY_E) == GLFW_PRESS)
		camera.TiltCameraRight();
	if (glfwGetKey(window.window_, GLFW_KEY_I) == GLFW_PRESS)
		camera.TurnCameraUpwards();
	if (glfwGetKey(window.window_, GLFW_KEY_K) == GLFW_PRESS)
		camera.TurnCameraDownwards();
	if (glfwGetKey(window.window_, GLFW_KEY_J) == GLFW_PRESS)
		camera.TurnCameraLeft();
	if (glfwGetKey(window.window_, GLFW_KEY_L) == GLFW_PRESS)
		camera.TurnCameraRight();

}

void Application::SetTransformationMatrices() {
	shaderData.viewMatrix = camera.View();
	shaderData.projectionMatrix = camera.SetDefaultProjection();
	shaderData.modelMatrix = glm::mat4(1.0f);

	glUniformMatrix4fv(v_eViewMatrix, 1, GL_FALSE, glm::value_ptr(shaderData.viewMatrix));
	glUniformMatrix4fv(v_eProjectionMatrix, 1, GL_FALSE, glm::value_ptr(shaderData.projectionMatrix));
	glUniformMatrix4fv(v_eModelMatrix, 1, GL_FALSE, glm::value_ptr(shaderData.modelMatrix));
}

void Application::ApplyMenuOptions() {
	// Render mode:
	switch (menu.menuData.render_mode) {
	case Points:
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); break;
	case Wireframe:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
	case Solid:
	default:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
	}

	// Scene light:
	shaderData.lightIntensity = menu.menuData.lightIntensity;
	shaderData.lightPosition = menu.menuData.lightPos;
	shaderData.shininess = menu.menuData.shininess;
	shaderData.IsLightAttenuationOn = menu.menuData.isLightAttenuationOn;
}

void Application::SetupSubroutines() {
	Shader mainShader = shaders.front();
	shaderData.subroutineIndices.applyAttenuationIndex = glGetSubroutineIndex(mainShader.program, GL_FRAGMENT_SHADER, "ApplyAttenuation");
	shaderData.subroutineIndices.dontAddModificationsIndex = glGetSubroutineIndex(mainShader.program, GL_FRAGMENT_SHADER, "DontAddModifications");
}

void Application::SetUniformValues() {
	glUniform3f(f_eLightIntensity, shaderData.lightIntensity.x, shaderData.lightIntensity.y, shaderData.lightIntensity.z);
	glUniform3f(f_eLightPosition, shaderData.lightPosition.x, shaderData.lightPosition.y, shaderData.lightPosition.z);
	glUniform1i(f_eShininess, shaderData.shininess);

	// Set subroutine to use attenuation or not
	if (shaderData.IsLightAttenuationOn) {
		glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &shaderData.subroutineIndices.applyAttenuationIndex);
	}
	else {
		glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &shaderData.subroutineIndices.dontAddModificationsIndex);
	}

	SetTransformationMatrices();
}
