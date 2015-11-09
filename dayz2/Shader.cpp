#include "Shader.h"

#include "GlobalSystem.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <GLFW\glfw3.h>

Shader::Shader(std::string filePath)
{
	loadShader(filePath);
}

Shader::~Shader()
{
}

void Shader::loadShader(std::string filePath)
{
	std::ifstream fileStream(filePath);

	if (!fileStream.is_open())
	{
		gSys->log("Error opening shader file " + filePath);
		exit(1);
	}

	std::stringstream contentSStream;
	contentSStream << fileStream.rdbuf();

	fileStream.close();

	std::string content = contentSStream.str();

	int delimiter = content.find("@");

	std::string vertShaderStr = content.substr(0, delimiter);
	std::string fragShaderStr = content.substr(delimiter + 1);
	const char *vertShaderSrc = vertShaderStr.c_str();
	const char *fragShaderSrc = fragShaderStr.c_str();


	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	GLint success;
	int logLength;

	//Vertex shader
	glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
	glCompileShader(vertShader);

	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<GLchar> vertShaderError(logLength);
		glGetShaderInfoLog(vertShader, logLength, NULL, &vertShaderError[0]);
		printf("Error compiling shader type %d: '%s'\n", GL_VERTEX_SHADER, vertShaderError);
	}


	//Fragment shader
	glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
	glCompileShader(fragShader);

	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<GLchar> fragShaderError(logLength);
		glGetShaderInfoLog(fragShader, logLength, NULL, &fragShaderError[0]);
		printf("Error compiling shader type %d: '%s'\n", GL_VERTEX_SHADER, fragShaderError);
	}

	program = glCreateProgram();
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (success == 0) {
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<GLchar> linkShaderError(logLength);
		glGetProgramInfoLog(program, logLength, NULL, &linkShaderError[0]);
		printf("Error linking shader program: '%s'\n", linkShaderError);
	}

	glValidateProgram(program);

	glGetProgramiv(program, GL_VALIDATE_STATUS, &success);
	if (!success) {
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<GLchar> validateShaderError(logLength);
		glGetProgramInfoLog(program, logLength, NULL, &validateShaderError[0]);
		printf("Invalid shader program: '%s'\n", validateShaderError);
		exit(1);
	}

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
}
