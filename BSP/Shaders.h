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

	void printShaders()
	{
		std::cout << "Fragement";
		std::cout << fragement;
		std::cout << "Vertex";
		std::cout << vertex;
	}
	void parseShaderCode(std::string path1, std::string path2)
	{
		std::ifstream vertexcode, fragementcode;
		std::stringstream code1, code2;
		std::string line;
		std::string vertCode;
		std::string fragCode;

		vertexcode.open(path1);
		while (getline(vertexcode, line))
			code1 << line << "\n";
		vertCode = code1.str();
		vertex = vertCode.c_str();
		vertexcode.close();

		fragementcode.open(path2);
		while (getline(fragementcode, line))
			code2 << line << "\n";
		fragCode = code2.str();
		fragement = fragCode.c_str();
		fragementcode.close();

		printShaders();
		vs = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vs, 1, &vertex, NULL);
		glCompileShader(vs);
		fs = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fs, 1, &fragement, NULL);
		glCompileShader(fs);
		
		shaderprogram = glCreateProgram();
		glAttachShader(shaderprogram, vs);
		glAttachShader(shaderprogram, fs);
		glLinkProgram(shaderprogram);
		glDeleteShader(fs);
		glDeleteShader(vs);
	}
	unsigned int getShderProgramID()
	{
		return shaderprogram;
	}
};

#endif
