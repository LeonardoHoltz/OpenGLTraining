// shader.h
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <vector>
#include <string>

class Shader {
private:
	typedef struct {
		GLenum type;
		const char* filename;
		GLuint shader;
	} ShaderInfo;

	std::vector<ShaderInfo> shader_files;

public:
	GLuint program;
	std::vector<std::pair<GLuint, std::string>> subroutines_vertex;
	std::vector<std::pair<GLuint, std::string>> subroutines_fragment;

	const GLchar* ReadShader(const char* filename);
	GLuint LoadShaders();
	void SetupShaders(const char* vertex_shader_filename, const char* fragment_shader_filename);
	void UseShaderProgram();

	// utility uniform functions
	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;

	// Subroutine indices
	void GetSubroutinesIndices(std::vector<std::string> vertex_shader_subroutines, std::vector<std::string> fragment_shader_subroutines);
	void SetSubroutines();
};

#endif // !SHADER_H
