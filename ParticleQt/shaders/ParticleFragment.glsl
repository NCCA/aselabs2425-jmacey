#version 410 core
layout(location =0) out vec4 fragColour;
in vec3 colour;
void main()
{
    vec2 cirCoord = 2.0 * gl_PointCoord - 1.0;
    if(dot(cirCoord,cirCoord) > 1.0)
    {
        discard;
    }


    fragColour.rgb=colour;
}