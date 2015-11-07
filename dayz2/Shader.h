#pragma once

#include <GL/glew.h>
#include <string>

class Shader
{
public:
	Shader(std::string filePath);
	~Shader();

	GLuint getProgram() { return program; }
private:
	void loadShader(std::string filePath);
	GLuint program;
};

