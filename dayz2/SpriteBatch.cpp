#include "SpriteBatch.h"
#include "GlobalSystem.h"
#include "GameState.h"
#include "AnimationLoader.h"
#include <glm\vec4.hpp>

CSpriteBatch::CSpriteBatch(int maxSprites) : m_bufferData(ELEMENTS_PER_VERTEX * 6 * maxSprites)
{

	glGenBuffers(1, &m_vb);
	glBindBuffer(GL_ARRAY_BUFFER, m_vb);
	//Float bytes * (xy + uv + rgba) * four corners made up by two triangles * maxSprites
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * ELEMENTS_PER_VERTEX * 6 * maxSprites, NULL, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_vb);
}

void CSpriteBatch::begin(GLuint texture)
{
	if (m_isDrawing)
		end();

	m_isDrawing = true;
	m_currentTexture = texture;
	m_vertices = 0;
}

void CSpriteBatch::end()
{
	if (!m_isDrawing)
		throw "SpriteBatch not in use!";

	//Upload vertex data
	glBindBuffer(GL_ARRAY_BUFFER, m_vb);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * ELEMENTS_PER_VERTEX * m_vertices, m_bufferData.data());

	//Bind diffuse
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_currentTexture);
	glUniform1i(glGetUniformLocation(static_cast<CGameState*>(gSys->pStateSystem->getCurrentState())->shader.getProgram(), "u_textureSampler"), 1);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//Position, uv, color
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * ELEMENTS_PER_VERTEX, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * ELEMENTS_PER_VERTEX, reinterpret_cast<void*>(sizeof(GLfloat) * 2));
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * ELEMENTS_PER_VERTEX, reinterpret_cast<void*>(sizeof(GLfloat) * 4));

	glDrawArrays(GL_TRIANGLES, 0, m_vertices);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	m_isDrawing = false;
	m_currentTexture = 0;
	m_vertices = 0;
	m_bufferData.clear();
}

void CSpriteBatch::setColor(float red, float green, float blue, float alpha)
{
	m_r = red;
	m_g = green;
	m_b = blue;
	m_a = alpha;
}

void CSpriteBatch::draw(float x, float y, int width, int height, float u1, float v1, float u2, float v2, float rotation)
{
	m_vertices += 6;
	
	float cosTheta = cos(rotation);
	float sinTheta = sin(rotation);


	//Bottom left'
	glm::vec2 p = glm::vec2(x, y);
	calcPoint(x+width / 2, y+height / 2, rotation, p, cosTheta, sinTheta);
	m_bufferData.push_back(p.x);
	m_bufferData.push_back(p.y);

	m_bufferData.push_back(u1);
	m_bufferData.push_back(v1);

	m_bufferData.push_back(m_r);
	m_bufferData.push_back(m_g);
	m_bufferData.push_back(m_b);
	m_bufferData.push_back(m_a);

	//Bottom right
	p = glm::vec2(x + width, y);
	calcPoint(x+width / 2, y+height / 2, rotation, p, cosTheta, sinTheta);
	m_bufferData.push_back(p.x);
	m_bufferData.push_back(p.y);

	m_bufferData.push_back(u2);
	m_bufferData.push_back(v1);

	m_bufferData.push_back(m_r);
	m_bufferData.push_back(m_g);
	m_bufferData.push_back(m_b);
	m_bufferData.push_back(m_a);

	//Top left
	p = glm::vec2(x, y + height);
	calcPoint(x+width / 2, y+height / 2, rotation, p, cosTheta, sinTheta);
	m_bufferData.push_back(p.x);
	m_bufferData.push_back(p.y);

	m_bufferData.push_back(u1);
	m_bufferData.push_back(v2);

	m_bufferData.push_back(m_r);
	m_bufferData.push_back(m_g);
	m_bufferData.push_back(m_b);
	m_bufferData.push_back(m_a);


	//Second triangle

	//Top left
	p = glm::vec2(x, y + height);
	calcPoint(x+width / 2, y+height / 2, rotation, p, cosTheta, sinTheta);
	m_bufferData.push_back(p.x);
	m_bufferData.push_back(p.y);

	m_bufferData.push_back(u1);
	m_bufferData.push_back(v2);

	m_bufferData.push_back(m_r);
	m_bufferData.push_back(m_g);
	m_bufferData.push_back(m_b);
	m_bufferData.push_back(m_a);

	//Bottom right
	p = glm::vec2(x + width, y);
	calcPoint(x+width / 2, y+height / 2, rotation, p, cosTheta, sinTheta);
	m_bufferData.push_back(p.x);
	m_bufferData.push_back(p.y);

	m_bufferData.push_back(u2);
	m_bufferData.push_back(v1);

	m_bufferData.push_back(m_r);
	m_bufferData.push_back(m_g);
	m_bufferData.push_back(m_b);
	m_bufferData.push_back(m_a);

	//Top right
	p = glm::vec2(x + width, y + height);
	calcPoint(x+width / 2, y+height / 2, rotation, p, cosTheta, sinTheta);
	m_bufferData.push_back(p.x);
	m_bufferData.push_back(p.y);

	m_bufferData.push_back(u2);
	m_bufferData.push_back(v2);

	m_bufferData.push_back(m_r);
	m_bufferData.push_back(m_g);
	m_bufferData.push_back(m_b);
	m_bufferData.push_back(m_a);
}

void CSpriteBatch::draw(CSprite* pSprite)
{
	if (pSprite->m_pAnim != nullptr)
	{
		auto uv = pSprite->m_pAnim->render();
		draw(pSprite->m_pos.x, pSprite->m_pos.y, pSprite->m_width, pSprite->m_height, uv.y, uv.x, uv.w, uv.z, pSprite->m_rotation);
	} else
		draw(pSprite->m_pos.x, pSprite->m_pos.y, pSprite->m_width, pSprite->m_height, pSprite->m_u1, pSprite->m_v1, pSprite->m_u2, pSprite->m_v2, pSprite->m_rotation);
}

void CSpriteBatch::calcPoint(float cx, float cy, float rot, glm::vec2& point, float cos, float sin)
{
	point.x -= cx;
	point.y -= cy;

	float x = point.x * cos - point.y * sin;
	float y = point.x * sin + point.y * cos;

	point.x = x + cx;
	point.y = y + cy;
}

CSpriteBatch::~CSpriteBatch()
{
	glDeleteBuffers(1, &m_vb);
}