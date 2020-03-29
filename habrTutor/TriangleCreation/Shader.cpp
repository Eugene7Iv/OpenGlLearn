#include "Shader.h"

Shader::Shader(const GLchar * vertexPath, const GLchar * fragmentPath)
{
	//preparing to read file
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::badbit);
	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();

	//build shaders
	GLuint vertex, fragment;
	buildShader<VertexShader>(vertex, vShaderCode);
	checkShaderBuild<VertexShader>(vertex);

	buildShader<FragmentShader>(fragment, fShaderCode);
	checkShaderBuild<FragmentShader>(fragment);
	//shader program
	program = glCreateProgram();
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);
	checkProgramLinking(program);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::~Shader()
{
}

void Shader::use()
{
	glUseProgram(program);
}

void Shader::checkProgramLinking(GLuint & program)
{
	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if (!success)
	{
		std::cout << "ERROR::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}
}
