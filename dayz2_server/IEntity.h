#pragma once

#include <glm/glm.hpp>

struct Player;

struct IEntity
{
	virtual ~IEntity() {}
	virtual void update(double dt) = 0;
	virtual void init() = 0;
	virtual void hit(Player* pPlayer, float angle) = 0;
	
	virtual void serialize(uint8_t* array) = 0;
	virtual uint16_t serializedSize() = 0;

	glm::vec2 m_pos;
	float m_width, m_height;
	float m_angle;
	uint32_t m_id;
	uint8_t m_type;
};
