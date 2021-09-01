#version 330 core
layout (location = 0) in vec3 aPos;

uniform float transx;
uniform float transy;
uniform float scaleX;
uniform float scaleY;

void main()
{
    gl_Position = vec4(aPos.x + transx, aPos.y + transy, aPos.z, 1.0);
}