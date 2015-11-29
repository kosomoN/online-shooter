#pragma once

#include <glm/glm.hpp>

struct IEntity
{
	virtual ~IEntity() {}
	virtual void update(double dt) = 0;
	virtual void init() = 0;
	
	virtual void serialize(uint8_t* array) = 0;
	virtual uint16_t serializedSize() = 0;

	glm::vec2 m_pos;
	uint32_t m_id;
	uint16_t m_type;
};
