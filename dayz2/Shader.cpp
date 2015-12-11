#include "Shader.h"

#include "GlobalSystem.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>

CShader::CShader(std::string filePath)
{
	loadShader(filePath);
	glUseProgram(program);
	mvpLocation = glGetUniformLocation(program, "mvp");
}

CShader::~CShader()
{
	glDeleteProgram(program);
}

void CShader::setMatrix(const glm::mat4 & matrix)
{
	glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}

void CShader::loadShader(std::string filePath)
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

	//Vertex shader
	glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
	glCompileShader(vertShader);


	//Fragment shader
	glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
	glCompileShader(fragShader);

	program = glCreateProgram();
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (success == GL_FALSE) {
		GLint maxSize;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxSize);

		std::vector<GLchar> log(maxSize);
		glGetProgramInfoLog(program, maxSize, &maxSize, &log[0]);
		gSys->log("\n\n ==============SHADER LOG==============");
		printf(log.data());
		gSys->log("\n\n ======================================");
	}

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
}
