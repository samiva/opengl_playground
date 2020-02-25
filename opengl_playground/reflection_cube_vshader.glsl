#version 450

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;

out vec3 vs_fs_normal;
out vec3 vs_fs_position;

uniform mat4 mat_mvp;
uniform mat4 mat_mv;

void main() {

    // Clip-space position
    gl_Position = mat_mvp * vec4(in_position, 1.0f);

    // View-space position normal and position
    vs_fs_normal = mat3(mat_mv) * in_normal;
    vs_fs_position = (mat_mv * vec4(in_position, 1.0f)).xyz; 

}