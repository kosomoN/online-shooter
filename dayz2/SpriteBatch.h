#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

class SpriteBatch
{
public:
	SpriteBatch(int maxSprites);
	~SpriteBatch();
	void begin(GLuint texture);
	void end();
	void draw(float x, float y, float z, float width, float height, float u1, float v1, float u2, float v2);
	void setColor(float r, float g, float b, float a);
private:
	int m_vertices;
	std::vector<GLfloat> m_bufferData;
	float m_r = 1, m_g = 1, m_b = 1, m_a = 1;
	GLuint m_vb, m_currentTexture;
	bool m_isDrawing;
};