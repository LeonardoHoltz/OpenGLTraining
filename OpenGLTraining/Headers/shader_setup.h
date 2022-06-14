// shader_setup.h
#ifndef SHADER_SETUP_H
#define SHADER_SETUP_H

#include <glad/glad.h>
#include <vector>

class ShaderSetup {
private:
	typedef struct {
		GLenum type;
		const char* filename;
		GLuint shader;
	} ShaderInfo;

	std::vector<ShaderInfo> shader_files;

public:
	GLuint program;

	const GLchar* ReadShader(const char* filename);
	GLuint LoadShaders();
	void SetupSingleTriangleShaders();
};

#endif // !SHADER_SETUP_H
