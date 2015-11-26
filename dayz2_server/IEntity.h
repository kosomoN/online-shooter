#pragma once

#include <glm/glm.hpp>

struct IEntity
{
	virtual void update() {};
	virtual void init() = 0;
	
	glm::vec2 m_pos;
	uint32_t m_id;
};
