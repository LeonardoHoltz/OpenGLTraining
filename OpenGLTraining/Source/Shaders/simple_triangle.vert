#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

layout (location = 2) uniform mat4 model_matrix;
layout (location = 3) uniform mat4 view_matrix;
layout (location = 4) uniform mat4 projection_matrix;

out vec2 TexCoord;

void main()
{
    //gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);

    vec4 vPosition = vec4(aPos, 1.0);

    gl_Position = projection_matrix * view_matrix *  model_matrix * vPosition;

    TexCoord = aTexCoord;
}