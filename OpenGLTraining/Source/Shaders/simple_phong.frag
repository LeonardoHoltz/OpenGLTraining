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

// Constants

const vec3 AMBIENT_COLOR_INTENSITY = vec3(0.3);

// Subroutines
subroutine vec4 Illumination(vec3 pos, vec3 normal, vec3 observer_pos, vec4 obj_color, vec3 light_pos);
subroutine uniform Illumination SetColor;

subroutine vec3 LightModification(vec3 light, vec3 light_pos, vec3 frag_pos);

subroutine uniform LightModification ApplyLightModifications;

// Functions

vec3 AmbientLight(vec3 color) {
    return color * AMBIENT_COLOR_INTENSITY;
}

vec3 DiffuseLight(vec3 normal,vec3 light_vector, vec3 color, vec3 light) {
    return max(0.0, dot(normal, light_vector)) * color * light;
}

vec3 SpecularLight(vec3 refraction_direction, vec3 view_direction, vec3 specular_map, vec3 light) {
    return light * pow(max(0.0,dot(refraction_direction, view_direction)), shineness) * vec3(specular_map);
}

vec3 SpecularLightBlinnPhong(vec3 light_direction, vec3 view_direction, vec3 normal, vec3 light) {
    vec3 h = normalize(view_direction + light_direction);
    return light * max(0.0, pow(dot(h, normal), shineness));
}

vec4 PhongReflectionModel(vec3 pos, vec3 normal, vec3 observer_pos, vec4 obj_color, vec4 specular_map, vec3 light_pos) {
    vec3 l = normalize(observer_pos + light_pos - pos);
    vec3 n = normalize(normal);
    vec3 v = normalize(observer_pos - pos);
    vec3 r = normalize(-l + 2 * n * dot(n, l));

    vec3 final_light = ApplyLightModifications(light_intensity, light_position, world_position);

    vec3 ambient_term  = AmbientLight(vec3(obj_color));
    vec3 diffuse_term  = DiffuseLight(n, l, vec3(obj_color), final_light);
    vec3 specular_term = SpecularLight(r, v, vec3(specular_map), final_light);

    vec3 phong_model = diffuse_term + ambient_term + specular_term;
    return vec4(phong_model.x, phong_model.y, phong_model.z, 1.0);
}

subroutine ( LightModification ) vec3 ApplyAttenuation(vec3 light, vec3 light_pos, vec3 frag_pos) {
    // The values here is following these instructions: https://wiki.ogre3d.org/tiki-index.php?page=-Point+Light+Attenuation
    float Kc = 1.0; // constant term
    float Kl = 0.35; // linear term
    float Kq = 0.44; // quadratic term
    float d = distance(light_pos, frag_pos);
    return light / (Kq * pow(d,2) + Kl * d + Kc);
}

subroutine ( LightModification ) vec3 DontAddModifications(vec3 light, vec3 light_pos, vec3 frag_pos) {
    return light;
}

void main()
{
    vec3 camera_position = vec3(inverse(view_matrix) * vec4(0.0, 0.0, 0.0, 1.0));
    vec4 obj_color_diffuse = texture(texture_diffuse1, frag_tex_coord);
    vec4 obj_color_specular = texture(texture_specular1, frag_tex_coord);
    FragColor = PhongReflectionModel(world_position, world_normal, camera_position, obj_color_diffuse, obj_color_specular, light_position);
}