#version 330
struct Light{
    vec3 pos;
    vec3 amibent;
    vec3 diffuse;
    vec3 specular;
};

struct Material{
    sampler2D tex;
    vec3 specular;
    float shiness;
};


in vec3 normal_viewspace;
in vec2 tex_coord;
in vec3 fragment_pos;

uniform Light light;
uniform Material material;

out vec4 FragColor;



vec3 get_ambient(){
    return light.amibent*vec3(texture(material.tex,tex_coord)).rgb;
}

vec3 get_diffuse(){
    return light.diffuse*max(dot(normal_viewspace,normalize(light.pos-fragment_pos)),0)*vec3(texture(material.tex,tex_coord)).rgb;
}
vec3 get_specular(){
    return light.specular*texture(material.tex,tex_coord).rgb*pow(max(dot(normalize(fragment_pos),normalize(reflect(light.pos-fragment_pos,normal_viewspace))),0),material.shiness);
}

void main() {

    FragColor = vec4(get_ambient()+get_specular()+get_diffuse(),1.0f);

}


