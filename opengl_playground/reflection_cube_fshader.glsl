#version 450 core

in vec3 vs_fs_normal;
in vec3 vs_fs_position;

// Final fragment color
layout (location = 0) out vec4 fcolor;

// the cube-map texture
uniform samplerCube tex;

void main() {
    // Calculate the texture coordinate by reflecting the view-space 
    // position around the surface normal
    vec3 tc = reflect(-vs_fs_position, normalize(vs_fs_normal));
    // Sample the texture and color color the resulting fragment a golden color.
    fcolor = vec4(0.3,0.2,0.1,1.0) + vec4(0.97, 0.83, 0.79, 0.0) * texture(tex, tc);
}