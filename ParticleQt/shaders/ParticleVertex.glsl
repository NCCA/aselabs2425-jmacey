#version 410 core

uniform mat4 MVP;
layout(location=0) in vec4 inPos;
layout(location=1) in vec3 inColour;
out vec3 colour;
void main()
{
    colour=inColour;
    gl_Position = MVP*vec4(inPos.xyz,1.0);
    gl_PointSize=inPos.w;
}