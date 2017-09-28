#pragma once

#include "glew.h"
#include "freeglut.h"
#include <iostream>

class ShaderLoader
{
private:
	std::string ReadShader(char* filename);
	GLuint CreateShader(GLenum shaderType, std::string source,
		char* shaderName);

public:
	ShaderLoader();
	~ShaderLoader();
	GLuint CreateProgram(char* VertexShaderFilename,
		char* FragmentShaderFilename);
};