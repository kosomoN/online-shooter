#pragma once

#include <glm\vec2.hpp>

struct IEntity
{
	virtual void update() {};
	virtual void init() = 0;
	
	virtual void setPosition(const glm::vec2& pos) { m_pos = pos; }
	virtual const glm::vec2& getPosition() { return m_pos; }
	virtual uint32_t getID() { return m_id; }
protected:
	glm::vec2 m_pos;
	uint32_t m_id;
};