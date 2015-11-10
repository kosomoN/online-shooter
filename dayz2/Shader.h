#pragma once

#include <GL/glew.h>
#include <string>
#include <glm/glm.hpp>

class Shader
{
public:
	Shader(std::string filePath);
	~Shader();

	GLuint getProgram() { return program; }
	void setMatrix(const glm::mat4& matrix);
private:
	void loadShader(std::string filePath);
	GLuint program;
	GLuint mvpLocation;
};

