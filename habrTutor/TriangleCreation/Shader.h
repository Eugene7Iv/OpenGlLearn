#pragma once

#include <fstream>
#include <sstream>
#include <iostream>

#include "GL/glew.h"
class Shader
{
	enum ShaderType
	{
		VertexShader,
		FragmentShader
	};

public:
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	virtual ~Shader();

	void use();
	GLuint& getProgram();

private:
	template<ShaderType T>
	void buildShader(GLuint& shader, const GLchar* shaderSourceCode)
	{
		switch (T)
		{
		case Shader::VertexShader:
			shader = glCreateShader(GL_VERTEX_SHADER);
			break;
		case Shader::FragmentShader:
			shader = glCreateShader(GL_FRAGMENT_SHADER);
			break;
		}
		glShaderSource(shader, 1, &shaderSourceCode, NULL);
		glCompileShader(shader);
	}

	template<ShaderType T>
	void checkShaderBuild(GLuint& shader)
	{
		GLint success;
		GLchar infoLog[512];
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);

			switch (T)
			{
			case VertexShader:
				std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
			case FragmentShader:
				std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
			default:
				std::cout << "ERROR::SHADER::UNKNOWN_SHADER_TYPE" << std::endl;
			}
		}
	}

	void checkProgramLinking(GLuint& program);
public:
	GLuint program;
};