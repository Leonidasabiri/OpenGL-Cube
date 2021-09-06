#version 330 core

out vec4 FragementColor;

in vec2 text2D;

uniform sampler2D texture1;

void main()
{
	//gl_FragColor.rgb = color;
	FragementColor = texture(texture1, text2D);
}