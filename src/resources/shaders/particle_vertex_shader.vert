#version 420 core

// the incoming vertex
layout (location = 0) in vec4 position;
layout (location = 1) in vec2 vertTexCoord;
layout (location = 3) in vec4 color;
layout (location = 4) in mat4 mv_matrix;

out VS_OUT
{
    vec4 color;
    vec2 fragTexCoord;
} vs_out;

uniform mat4 camera_matrix;
uniform mat4 proj_matrix;


void main(void)
{
    // Calculate coordinate in view-space
    vec4 P = camera_matrix * mv_matrix * position;

    // Send the color output to the fragment shader
    vs_out.color = color;

    // Pass the texture coordinate to the fragment shader
    vs_out.fragTexCoord = vertTexCoord;

    // Calculate the clip-space position of each vertex
    // adding here the transformations we get steady light
    gl_Position = proj_matrix * P;
}