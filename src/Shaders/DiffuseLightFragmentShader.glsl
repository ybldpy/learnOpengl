#version 330 core

struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shine;
};
struct Light{
    vec3 pos;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


in vec3 Normal;
in vec3 FragPos;
//uniform vec3 cam_pos;
uniform Material material;
uniform Light light;
out vec4 FragColor;



void main() {
//    vec3 diffuse = max(dot(normalize(light_pos-FragPos),Normal),0)*light;
//    vec3 sp = pow(max(dot(reflect(normalize(light_pos-FragPos),Normal),normalize(FragPos)),0.0),45)*light*0.4;
//    FragColor = vec4((ambient+diffuse+sp)*object_color,1.0);
    vec3 ambient = light.ambient*material.ambient;
    vec3 diffuse = light.diffuse*max(dot(normalize(light.pos-FragPos),Normal),0)*material.diffuse;
    vec3 specular = light.specular*pow(max(dot(normalize(FragPos),normalize(reflect(light.pos-FragPos,Normal))),0.0),material.shine)*material.specular;
    FragColor = vec4(ambient+diffuse+specular,1.0f);
}
