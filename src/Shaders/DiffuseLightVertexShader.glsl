#version 330 core
layout (location=0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
uniform mat4 trans;
uniform mat4 model;
uniform mat4 view;
uniform vec3 light_model_pos;
out vec3 Normal;
out vec3 FragPos;

void main(){
    gl_Position = trans*vec4(aPos,1.0);
    //vec3 t1 = vec3(view*mat4(mat3(transpose(inverse(model))))*vec4(aNormal,0.0));
    //vec3 t1 = mat3(transpose(inverse(view*model)))*aNormal;
    Normal = normalize(vec3(transpose(inverse(view*model))*vec4(aNormal,0.0)));//vec3(transpose(inverse(view*model))*vec4(aNormal,0));mat3(transpose(inverse(view*model)))*aNormal;
    FragPos = vec3(view*model*vec4(aPos,1.0));

}