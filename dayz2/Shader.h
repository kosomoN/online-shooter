#pragma once

#include <GL/glew.h>
#include <string>
#include <glm/glm.hpp>

class CShader
{
public:
	CShader(std::string filePath);
	~CShader();

	GLuint getProgram() { return program; }
	void setMatrix(const glm::mat4& matrix);
private:
	void loadShader(std::string filePath);
	GLuint program;
	GLuint mvpLocation;
};

