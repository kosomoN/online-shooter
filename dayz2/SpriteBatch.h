#pragma once

#include <GL/glew.h>
#include <vector>
#include "Sprite.h"

const int ELEMENTS_PER_VERTEX = 8;

class CSpriteBatch
{
public:
	CSpriteBatch(int maxSprites);
	~CSpriteBatch();
	void begin(GLuint texture);
	void end();
	void draw(float x, float y, float width, float height, float u1, float v1, float u2, float v2, float rotation, glm::vec2 rotPoint);
	void drawVertices(const float& x1, const float& y1, const float& x2, const float& y2, const float& u1, const float& v1, const float& u2, const float& v2);
	void drawUI(const float& x1, const float& y1, const float& x2, const float& y2, const float& u1, const float& v1, const float& u2, const float& v2);
	void draw(CSprite* pSprite);
	void setColor(float r, float g, float b, float a);
	GLuint getCurrentTexture() { return  m_currentTexture; }
private:
	void calcPoint(glm::vec2 rotationPoint, float rot, glm::vec2& point, float cos, float sin);
	int m_vertices, m_maxVertices, m_index = 0;
	std::vector<GLfloat> m_bufferData;
	float m_r = 1, m_g = 1, m_b = 1, m_a = 1;
	GLuint m_vb, m_currentTexture;
	bool m_isDrawing;
};