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
	models_loaded.push_back(model);
}

void Application::DrawScene(Shader shader) {
	for (Model & model : models_loaded) {
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
	shader_data.view_matrix = camera.View();
	shader_data.projection_matrix = camera.SetDefaultProjection();
	shader_data.model_matrix = glm::mat4(1.0f);

	glUniformMatrix4fv(vViewMatrix, 1, GL_FALSE, glm::value_ptr(shader_data.view_matrix));
	glUniformMatrix4fv(vProjectionMatrix, 1, GL_FALSE, glm::value_ptr(shader_data.projection_matrix));
	glUniformMatrix4fv(vModelMatrix, 1, GL_FALSE, glm::value_ptr(shader_data.model_matrix));
}

void Application::ApplyMenuOptions() {
	// Render mode:
	switch (menu.menu_data.render_mode) {
	case Points:
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); break;
	case Wireframe:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
	case Solid:
	default:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
	}

	// Scene light:
	shader_data.light_intensity = menu.menu_data.light_intensity;
	shader_data.light_position = menu.menu_data.light_pos;
	shader_data.shininess = menu.menu_data.shininess;
}

void Application::SetUniformValues() {
	glUniform3f(fLightIntensity, shader_data.light_intensity.x, shader_data.light_intensity.y, shader_data.light_intensity.z);
	glUniform3f(fLightPosition, shader_data.light_position.x, shader_data.light_position.y, shader_data.light_position.z);
	glUniform1i(fShininess, shader_data.shininess);
	SetTransformationMatrices();
}