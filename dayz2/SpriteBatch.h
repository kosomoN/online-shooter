#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Sprite.h"

const int ELEMENTS_PER_VERTEX = 8;

class SpriteBatch
{
public:
	SpriteBatch(int maxSprites);
	~SpriteBatch();
	void begin(GLuint texture);
	void end();
	void draw(float x, float y, float width, float height, float u1, float v1, float u2, float v2);
	void draw(Sprite* pSprite);
	void setColor(float r, float g, float b, float a);
	GLuint getCurrentTexture() { return  m_currentTexture; }
private:
	int m_vertices;
	std::vector<GLfloat> m_bufferData;
	float m_r = 1, m_g = 1, m_b = 1, m_a = 1;
	GLuint m_vb, m_currentTexture;
	bool m_isDrawing;


};