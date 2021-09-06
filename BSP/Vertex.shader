#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 tex2D;

out vec3 col;
out vec2 text2D;

uniform mat4 transform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos ,1.0);
    text2D = vec2(tex2D.x,tex2D.y);
}