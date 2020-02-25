#version 450 core

in vec3 vcolor;
in vec3 vtexcoord;

uniform samplerCube skyboxtex;

out vec4 fcolor;

void main() {
    fcolor = texture(skyboxtex, vtexcoord)*vec4(vcolor,1);
}