#version 330
layout (location = 0) in vec3 vertex_pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texture_coord;
uniform mat4 trans;
uniform mat4 trans_normal;
uniform mat4 model_view;
out vec3 normal_viewspace;
out vec2 tex_coord;
out vec3 fragment_pos;


void main() {
    gl_Position = trans*vec4(vertex_pos,1.0f);
    normal_viewspace = vec3(trans_normal*vec4(normal,0));
    tex_coord = texture_coord;
    fragment_pos = vec3(model_view*vec4(vertex_pos,1.0f));
    normal_viewspace = vec3(normalize(trans_normal*vec4(normal,0.0f)));

}
