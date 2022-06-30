#version 460 core

uniform vec4 menuColor;     // color selected by the user

layout (location = 3) uniform mat4 model_matrix;
layout (location = 4) uniform mat4 view_matrix;
layout (location = 5) uniform mat4 projection_matrix;

layout (location = 6) uniform vec3 light_intensity;
layout (location = 7) uniform int shineness;
layout (location = 8) uniform vec3 light_position;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal;

in vec3 world_position;
in vec3 world_normal;
in vec2 fTexCoord;

out vec4 FragColor;

// Subroutines
subroutine vec4 Illumination(vec3 pos, vec3 normal, vec3 observer_pos, vec4 obj_color, vec3 light_pos);

subroutine uniform Illumination SetColor;

vec4 PhongReflectionModel(vec3 pos, vec3 normal, vec3 observer_pos, vec4 obj_color, vec3 light_pos) {
    vec3 l = normalize(observer_pos + light_pos - pos);
    vec3 n = normalize(normal);
    vec3 v = normalize(observer_pos - pos);
    vec3 r = normalize(-l + 2 * n * dot(n, l));
    //vec4 h = normalize(v+l); // for later Blinn-Phong
    vec3 diffuse_term = max(0.0, dot(n, l)) * vec3(obj_color.x, obj_color.y, obj_color.z) * light_intensity;
    vec3 ambient_term = vec3(obj_color.x, obj_color.y, obj_color.z) * vec3(0.3, 0.3, 0.3);
    //vec3 specular_term = light_intensity * max(0.0, pow(dot(h,n), shineness)); // for later Blinn-Phong
    vec3 specular_term = light_intensity * pow(max(0.0,dot(r,v)), shineness);
    vec3 phong_model = diffuse_term + ambient_term + specular_term;
    return vec4(phong_model.x, phong_model.y, phong_model.z, 1.0);
}

void main()
{
    vec3 camera_position = vec3(inverse(view_matrix) * vec4(0.0, 0.0, 0.0, 1.0));
    vec4 obj_color = texture(texture_diffuse1, fTexCoord);
    FragColor = PhongReflectionModel(world_position, world_normal, camera_position, obj_color, light_position);
    //FragColor = PhongReflectionModel(world_position, world_normal, camera_position, vec4(1.0, 0.0, 0.0, 0.0), light_position);
}