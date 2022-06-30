#include "../Headers/shader.h"

#include <iostream>

void Shader::SetupShaders(const char* vertex_shader_filename, const char* fragment_shader_filename) {

	shader_files.push_back({ GL_VERTEX_SHADER, vertex_shader_filename });
	shader_files.push_back({ GL_FRAGMENT_SHADER, fragment_shader_filename });
	shader_files.push_back({ GL_NONE, NULL });
    program = LoadShaders();
    glUseProgram(program);
}

const GLchar* Shader::ReadShader(const char* filename)
{
    FILE* infile;

    errno_t err = fopen_s(&infile, filename, "rb");

    if (!infile) {
        std::cerr << "Unable to open file '" << filename << "': " << err << std::endl;
        throw std::runtime_error("Failed to read shaders.");
    }

    fseek(infile, 0, SEEK_END);
    int len = ftell(infile);
    fseek(infile, 0, SEEK_SET);


    if (len != -1L) { // prevent overflow of size if ftell fails
        GLchar* source = new GLchar[len + 1];
        fread(source, 1, static_cast<size_t>(len), infile);
        source[len] = 0;
        fclose(infile);
        return const_cast<const GLchar*>(source);
    }
    else {
        fclose(infile);
        return nullptr;
    }
}

GLuint Shader::LoadShaders()
{
    if (shader_files.empty()) { return 0; }

    GLuint program = glCreateProgram();

    for (ShaderInfo & entry : shader_files) {
        if (entry.type != GL_NONE) {
            GLuint shader = glCreateShader(entry.type);
            entry.shader = shader;
            const GLchar* source = ReadShader(entry.filename);
            if (source == NULL) {
                for (ShaderInfo& delete_entry : shader_files) {
                    glDeleteShader(delete_entry.shader);
                    delete_entry.shader = 0;
                }
                std::cerr << "Shader reading failed\n";
                return 0;
            }

            glShaderSource(shader, 1, &source, NULL);
            delete[] source;

            glCompileShader(shader);

            GLint compiled;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
            if (!compiled) {
                GLsizei len;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

                GLchar* log = new GLchar[len + 1];
                glGetShaderInfoLog(shader, len, &len, log);
                std::cerr << "Shader compilation failed: " << log << std::endl;
                delete[] log;

                return 0;
            }

            glAttachShader(program, shader);
        }
    }

    glLinkProgram(program);

    GLint linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked) {
        GLsizei len;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);

        GLchar* log = new GLchar[len + 1];
        glGetProgramInfoLog(program, len, &len, log);
        std::cerr << "Shader linking failed: " << log << std::endl;
        delete[] log;

        for (ShaderInfo& delete_entry : shader_files) {
            glDeleteShader(delete_entry.shader);
            delete_entry.shader = 0;
        }

        return 0;
    }

    // Since we no longer need the shaders once they`re linked, we can detele them.
    for (ShaderInfo& delete_entry : shader_files) {
        glDeleteShader(delete_entry.shader);
    }

    std::cout << "Shaders Loaded correctly!\n";

    return program;
}

void Shader::UseShaderProgram() {
    glUseProgram(program);
}

// Uniform functions

void Shader::SetBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(program, name.c_str()), (int)value);
}
void Shader::SetInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(program, name.c_str()), value);
}
void Shader::SetFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(program, name.c_str()), value);
}

// Subroutines

void Shader::GetSubroutinesIndices(std::vector<std::string> vertex_shader_subroutines, std::vector<std::string> fragment_shader_subroutines) {
    for (std::string subroutine_name : vertex_shader_subroutines) {
        GLuint subroutine_index = glGetSubroutineIndex(program, GL_VERTEX_SHADER, subroutine_name.c_str());
        subroutines_vertex.push_back(std::make_pair(subroutine_index, subroutine_name));
    }
    for (std::string subroutine_name : vertex_shader_subroutines) {
        GLuint subroutine_index = glGetSubroutineIndex(program, GL_FRAGMENT_SHADER, subroutine_name.c_str());
        subroutines_fragment.push_back(std::make_pair(subroutine_index, subroutine_name));
    }
}

void Shader::SetSubroutines() {

}