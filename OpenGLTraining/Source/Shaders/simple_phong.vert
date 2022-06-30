#version 460 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texture_coordinates;

layout (location = 3) uniform mat4 model_matrix;
layout (location = 4) uniform mat4 view_matrix;
layout (location = 5) uniform mat4 projection_matrix;

out vec3 world_position;
out vec3 world_normal;
out vec2 fTexCoord;

void main()
{
    vec4 homogeneous_position = vec4(position, 1.0);
    vec4 homogeneous_normal = vec4(normal, 1.0);
    gl_Position = projection_matrix * view_matrix *  model_matrix * homogeneous_position;

    // If we use a illumination algorithm in the vertex shader (Gouraud), the camera position can be useful...
    //vec4 camera_position = inverse(view_matrix) * vec4(0.0, 0.0, 0.0, 1.0);

    world_position = vec3(model_matrix * homogeneous_position);
    world_normal = vec3(inverse(transpose(model_matrix)) * homogeneous_normal);

    fTexCoord = texture_coordinates;
}