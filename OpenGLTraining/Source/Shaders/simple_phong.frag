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
in vec2 frag_tex_coord;

out vec4 FragColor;

// Subroutines
subroutine vec4 Illumination(vec3 pos, vec3 normal, vec3 observer_pos, vec4 obj_color, vec3 light_pos);

subroutine uniform Illumination SetColor;

vec3 ambient_color_intensity = vec3(0.3);

vec3 AmbientLight(vec3 color) {
    return color * ambient_color_intensity;
}

vec3 DiffuseLight(vec3 normal,vec3 light_vector, vec3 color) {
    return max(0.0, dot(normal, light_vector)) * color * light_intensity;
}

vec3 SpecularLight(vec3 refraction_direction, vec3 view_direction, vec3 specular_map) {
    return light_intensity * pow(max(0.0,dot(refraction_direction, view_direction)), shineness) * vec3(specular_map);
}

vec3 SpecularLightBlinnPhong(vec3 light_direction, vec3 view_direction, vec3 normal) {
    vec3 h = normalize(view_direction + light_direction);
    return light_intensity * max(0.0, pow(dot(h, normal), shineness));
}

vec4 PhongReflectionModel(vec3 pos, vec3 normal, vec3 observer_pos, vec4 obj_color, vec4 specular_map, vec3 light_pos) {
    vec3 l = normalize(observer_pos + light_pos - pos);
    vec3 n = normalize(normal);
    vec3 v = normalize(observer_pos - pos);
    vec3 r = normalize(-l + 2 * n * dot(n, l));

    vec3 diffuse_term  = DiffuseLight(n, l, vec3(obj_color));
    vec3 ambient_term  = AmbientLight(vec3(obj_color));
    vec3 specular_term = SpecularLight(r, v, vec3(specular_map));

    vec3 phong_model = diffuse_term + ambient_term;
    return vec4(phong_model.x, phong_model.y, phong_model.z, 1.0);
}



void main()
{
    vec3 camera_position = vec3(inverse(view_matrix) * vec4(0.0, 0.0, 0.0, 1.0));
    vec4 obj_color_diffuse = texture(texture_diffuse1, frag_tex_coord);
    vec4 obj_color_specular = texture(texture_specular1, frag_tex_coord);
    FragColor = PhongReflectionModel(world_position, world_normal, camera_position, obj_color_specular, obj_color_specular, light_position);
}