#version 450 core

layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec3 in_color;

uniform mat4 mvp; 

out vec3 vcolor;
out vec3 vtexcoord;

void main() {
    gl_Position = mvp*vec4(in_pos, 1);
    vcolor = in_color;
    vtexcoord = in_pos;
}