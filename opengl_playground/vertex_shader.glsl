#version 450 core

layout (location = 0) in vec3 vpos;
layout (location = 1) in vec2 vtexcoord;

out vec2 vstexcoord;

uniform mat4 transform;

void main() {
    vstexcoord = vtexcoord;
    gl_Position = transform*vec4(vpos,1.0);
}