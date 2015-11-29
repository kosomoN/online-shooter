#pragma once

#include <glm\vec2.hpp>
#include "LerpVec2.h"

struct IEntity
{
	virtual ~IEntity() {};
	virtual void update() {};
	virtual void init() = 0;
	
	virtual uint32_t getID() { return m_id; }
	virtual void parsePacket(uint8_t* data, unsigned int length) = 0;
	LerpVec2 m_pos;
protected:
	uint32_t m_id;
};