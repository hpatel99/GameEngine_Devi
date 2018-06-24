// TEXTURE RENDER - Vertex Shader
#version 400 core

uniform mat4 world_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;

// location is set 
layout (location = 0) in vec4 position;
layout (location = 1) in vec2 tc;

out VS_OUT
{
    vec2 textCoordinate;
} vs_out;

void main(void)
{
    vs_out.textCoordinate = tc;
    gl_Position = proj_matrix * view_matrix * world_matrix * position;
}
