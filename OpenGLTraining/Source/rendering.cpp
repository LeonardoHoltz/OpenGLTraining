#include "../Headers/rendering.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../Headers/stb_image.h"

#include <iostream>

#include <glm/gtc/type_ptr.hpp>

#include "../Headers/callbacks.h"

std::vector<GLfloat> test_triangle = {
	// positions			// texture coordinates
	-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,
	 0.5f, -0.5f, 0.0f,		1.0f, 0.0f,
	-0.5f,  0.5f, 0.0f,		0.0f, 1.0f,

	 0.5f, -0.5f, 0.0f,		1.0f, 0.0f,
	 0.5f,  0.5f, 0.0f,		1.0f, 1.0f,
	-0.5f,  0.5f, 0.0f,		0.0f, 1.0f,
};

Rendering::Rendering(Window& pWindow) : window(pWindow) {}

void Rendering::DefineCallbacks() {
	Callbacks callbacks(window, camera);
}

void Rendering::ClearScreen(glm::vec4 clear_color) {
	glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Rendering::PrepareDataForRendering() {
	DefineShaders();
	DefineVAOs();
	BindMainObjectVertexArray();
	DefineVBOs();
	BindMainObjectBuffer();
	CopyDataToCurrentArrayBuffer(test_triangle);

	GetUniformIDs();
}

void Rendering::GetUniformIDs() {
	shader_uniforms.menuColor = glGetUniformLocation(shader_setup.program, "menuColor");
}

void Rendering::SetUniformValues(ImguiMenuData& menu_data) {
	glUniform4f(shader_uniforms.menuColor, menu_data.triangle_color.r, menu_data.triangle_color.g, menu_data.triangle_color.b, menu_data.triangle_color.a);
}

void Rendering::DefineShaders() {
	shader_setup.SetupSingleTriangleShaders();
}

void Rendering::DefineVBOs() {
	glGenBuffers(numBuffers, Buffers);
}

void Rendering::DefineVAOs() {
	glGenVertexArrays(numVertexArrays, VertexArrays);
}

void Rendering::CopyDataToCurrentArrayBuffer(std::vector<GLfloat> vertices) {
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vPosition);
}

void Rendering::BindMainObjectBuffer() {
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[mainObjectVBO]);
}

void Rendering::BindMainObjectVertexArray() {
	glBindVertexArray(VertexArrays[mainObjectVAO]);
}

void Rendering::SetTransformationMatrices() {
	view_matrix = camera.View();
	projection_matrix = camera.SetDefaultProjection();
	model_matrix = glm::mat4(1.0f);

	glUniformMatrix4fv(vViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix));
	glUniformMatrix4fv(vProjectionMatrix, 1, GL_FALSE, glm::value_ptr(projection_matrix));
	glUniformMatrix4fv(vModelMatrix, 1, GL_FALSE, glm::value_ptr(model_matrix));
}

void Rendering::DefineTexture(ImguiMenuData& menu_data) {

	stbi_set_flip_vertically_on_load(true);

	glGenTextures(numTextures, Textures);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Textures[triangle_text]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, &menu_data.triangle_color.r);

	// Mipmap trilinear
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	const char* tex_filename = "C:\\Users\\br31427\\Pictures\\no_bitches.jpg";
	//const char* tex_filename = "C:\\Users\\br31427\\Pictures\\wall.jpg";
	void* tex_data = stbi_load(tex_filename, &width, &height, &nrChannels, 0);

	if (tex_data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_data);
		glGenerateMipmap(GL_TEXTURE_2D);
		std::cout << "Texture loaded correctly.";
	}
	else {
		throw std::runtime_error("Failed to load texture");
	}

	stbi_image_free(tex_data);

	ApplyTextDataToShader(test_triangle);
}

void Rendering::ApplyTextDataToShader(std::vector<GLfloat> vertices_text) {
	glVertexAttribPointer(vTextureCoord, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), BUFFER_OFFSET(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(vTextureCoord);
}

void Rendering::BindMainObjectTexture() {
	glBindTexture(GL_TEXTURE_2D, Textures[triangle_text]);
}

void Rendering::CalculateFramerate() {
	camera.CalculateFrameRate();
}

void Rendering::CheckForInputs() {
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