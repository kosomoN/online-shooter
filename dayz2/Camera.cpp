#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include "GlobalSystem.h"

CCamera::CCamera(float width, float height)
{
	resize(width, height);
}


CCamera::~CCamera()
{
}

void CCamera::resize(float width, float height)
{
	m_size.x = width;
	m_size.y = height;

	m_projection = glm::ortho(-width / 2.f, width / 2.f, -height / 2.f, height / 2.f);
	m_combined = m_projection * m_translation;
}

void CCamera::setPosition(const glm::vec2& pos)
{
	
	m_pos = glm::vec3(pos.x, pos.y, 0) + glm::vec3(shake, 0);

	if (m_pos.x - m_size.x / 2 < 0)
		m_pos.x = m_size.x / 2;

	if (m_pos.y - m_size.y / 2 < 0)
		m_pos.y = m_size.y / 2;
	
	if (m_pos.x + m_size.x / 2 > 32)
		m_pos.x = 32 - m_size.x / 2;

	if (m_pos.y + m_size.y / 2 > 32)
		m_pos.y = 32 - m_size.y / 2;

	//TODO Make framerate independant
	shake *= 0.9f;
	m_translation = glm::translate(glm::mat4(1.0f), -m_pos);
	m_combined = m_projection * m_translation;
}
