#version 450 core

uniform sampler2D tex;
in vec2 vstexcoord;
out vec4 fColor;

void main() {
    // fColor =vec4(1.0f,0.0f,0.0f,1.0f);
    fColor = texture(tex, vstexcoord);
}