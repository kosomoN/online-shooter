#include "SpriteBatch.h"
#include <GLFW\glfw3.h>

SpriteBatch::SpriteBatch(int maxSprites) : m_bufferData((3 + 2 + 4) * 6 * maxSprites)
{
	glGenBuffers(1, &m_vb);
	glBindBuffer(GL_ARRAY_BUFFER, m_vb);
	//Float bytes * (xyz + uv + rgba) * four corners made up by two triangles * maxSprites
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (3 + 2 + 4) * 6 * maxSprites, NULL, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_vb);
}

void SpriteBatch::begin(GLuint texture)
{
	if (m_isDrawing)
		throw "SpriteBatch already in use!";

	m_isDrawing = true;
	m_currentTexture = texture;
	m_vertices = 0;
}

void SpriteBatch::end()
{
	if (!m_isDrawing)
		throw "SpriteBatch not in use!";

	//Upload vertex data
	glBindBuffer(GL_ARRAY_BUFFER, m_vb);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * (3 + 2 + 4) * m_vertices, m_bufferData.data());

	//Bind diffuse
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_currentTexture);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//Position, uv, color
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 9, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 9, reinterpret_cast<void*>(sizeof(GLfloat) * 3));
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 9, reinterpret_cast<void*>(sizeof(GLfloat) * 5));

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

void SpriteBatch::setColor(float red, float green, float blue, float alpha)
{
	m_r = red;
	m_g = green;
	m_b = blue;
	m_a = alpha;
}

void SpriteBatch::draw(float x, float y, float z, float width, float height, float u1, float v1, float u2, float v2)
{
	m_vertices += 6;

	//Bottom left
	m_bufferData.push_back(x);
	m_bufferData.push_back(y);
	m_bufferData.push_back(z);
	
	m_bufferData.push_back(u1);
	m_bufferData.push_back(v1);

	m_bufferData.push_back(m_r);
	m_bufferData.push_back(m_g);
	m_bufferData.push_back(m_b);
	m_bufferData.push_back(m_a);

	//Bottom right
	m_bufferData.push_back(x + width);
	m_bufferData.push_back(y);
	m_bufferData.push_back(z);
	
	m_bufferData.push_back(u2);
	m_bufferData.push_back(v1);

	m_bufferData.push_back(m_r);
	m_bufferData.push_back(m_g);
	m_bufferData.push_back(m_b);
	m_bufferData.push_back(m_a);

	//Top left
	m_bufferData.push_back(x);
	m_bufferData.push_back(y + height);
	m_bufferData.push_back(z);
	
	m_bufferData.push_back(u1);
	m_bufferData.push_back(v2);

	m_bufferData.push_back(m_r);
	m_bufferData.push_back(m_g);
	m_bufferData.push_back(m_b);
	m_bufferData.push_back(m_a);


	//Second triangle

	//Top left
	m_bufferData.push_back(x);
	m_bufferData.push_back(y + height);
	m_bufferData.push_back(z);
	
	m_bufferData.push_back(u1);
	m_bufferData.push_back(v2);

	m_bufferData.push_back(m_r);
	m_bufferData.push_back(m_g);
	m_bufferData.push_back(m_b);
	m_bufferData.push_back(m_a);

	//Bottom right
	m_bufferData.push_back(x + width);
	m_bufferData.push_back(y);
	m_bufferData.push_back(z);
	
	m_bufferData.push_back(u2);
	m_bufferData.push_back(v1);

	m_bufferData.push_back(m_r);
	m_bufferData.push_back(m_g);
	m_bufferData.push_back(m_b);
	m_bufferData.push_back(m_a);

	//Top right
	m_bufferData.push_back(x + width);
	m_bufferData.push_back(y + height);
	m_bufferData.push_back(z);
	
	m_bufferData.push_back(u2);
	m_bufferData.push_back(v2);

	m_bufferData.push_back(m_r);
	m_bufferData.push_back(m_g);
	m_bufferData.push_back(m_b);
	m_bufferData.push_back(m_a);
}

SpriteBatch::~SpriteBatch()
{
	glDeleteBuffers(1, &m_vb);
}