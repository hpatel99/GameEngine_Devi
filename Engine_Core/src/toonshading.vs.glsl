#version 410 core

uniform mat4 world_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;

layout (location = 0) in vec4 position;
layout (location = 2) in vec3 normal;

out VS_OUT
{
    vec3 normal;
    vec3 view;
} vs_out;

void main(void)
{
    vec4 pos_vs = view_matrix * world_matrix * position;

    // Calculate eye-space normal and position
    vs_out.normal = mat3(view_matrix * world_matrix) * normal;
    vs_out.view = pos_vs.xyz;

    // Send clip-space position to primitive assembly
    gl_Position = proj_matrix * view_matrix * world_matrix * position;
}
 