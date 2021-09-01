#version 330 core

uniform vec3 color;
void main()
{
	gl_FragColor.rgb = color;
}