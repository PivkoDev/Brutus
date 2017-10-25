#pragma once

#include "glew.h"
#include "freeglut.h"
#include <iostream>
#include <map>

class ShaderManager
{
private:
	std::string 
	ReadShader(const std::string& filename);

	GLuint 
	CreateShader(
		GLenum shader_type,
		const std::string& source,
		const std::string& shader_name);

	static
	std::map<std::string, GLuint> programs;

public:
	ShaderManager();
	~ShaderManager();
	
	void 
	CreateProgram(
		const std::string& shader_name,
		const std::string& vertex_shader_filename,
		const std::string& fragment_shader_filename);

	static const GLuint 
	GetShader(const std::string&);

};