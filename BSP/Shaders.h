#pragma once
#ifndef SHADERS_H
#define SHADERS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>

#include <iostream>

class Shader
{
public:
	const char* vertex;
	const char* fragement;
	
	unsigned int vs, fs, shaderprogram;

	/*void printShaders()
	{
		std::cout << "Fragement";
		std::cout << fragement;
		std::cout << "Vertex";
		std::cout << vertex;
	}*/
	void parseShaderCode(std::string path1, std::string path2);
	unsigned int getShderProgramID();
	void destroyShader()
	{
		glDeleteShader(fs);
		glDeleteShader(vs);
	}
	~Shader()
	{
		destroyShader();
	}
};

#endif
