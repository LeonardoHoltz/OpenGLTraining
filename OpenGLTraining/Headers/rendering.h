#ifndef RENDERING_H
#define RENDERING_H

#include <glm/vec4.hpp>

#include <glad/glad.h>

#include "shader_setup.h"
#include "imgui_menu.h"
#include "camera.h"
#include "window.h"

#define BUFFER_OFFSET(a) ((void*)(a))

#define CLEAR_COLOR_BLACK glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)

class Rendering {
private:
    enum VBOs { mainObjectVBO = 0, numBuffers = 1 };
    enum VAOs { mainObjectVAO = 0, numVertexArrays = 1 };
    enum TextureIds { triangle_text = 0, numTextures = 1 };

    GLuint Buffers[numBuffers];
    GLuint VertexArrays[numVertexArrays];
    GLuint Textures[numTextures];

    // 'v' for vertex shader attributes and 'f' for fragment shader attributes???
    enum AttributePointers { vPosition = 0, vTextureCoord = 1, vModelMatrix = 2, vViewMatrix = 3, vProjectionMatrix = 4 };

    typedef struct {
        GLuint menuColor;
    } ShaderUniforms;

    void GetUniformIDs();

    /* Window which will be rendered our scenario*/
    Window& window;

public:
    ShaderSetup shader_setup;
    ShaderUniforms shader_uniforms;
    Camera camera;

    // TODO: Suggestion for later when we have more than one object being rendered.
    //std::vector<std::pair<glm::mat4, objID>> model_matrices;

    // TODO: Analyze if it's better to send just the MVP matrix to the shader.
    glm::mat4 model_matrix;
    glm::mat4 view_matrix;
    glm::mat4 projection_matrix;

    Rendering(Window&);

    void DefineCallbacks();
    void ClearScreen(glm::vec4 clear_color);
    void PrepareDataForRendering();
    void DefineShaders();
    void DefineVBOs();
    void DefineVAOs();
    void BindMainObjectBuffer();
    void BindMainObjectVertexArray();
    void CopyDataToCurrentArrayBuffer(std::vector<GLfloat> vertices);
    void SetUniformValues(ImguiMenuData& menu_data);
    void SetTransformationMatrices();

    void DefineTexture(ImguiMenuData& menu_data);
    void ApplyTextDataToShader(std::vector<GLfloat> vertices_text);
    void BindMainObjectTexture();

    void CalculateFramerate();
    void CheckForInputs();
};

#endif // RENDERING_H
