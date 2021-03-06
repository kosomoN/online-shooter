#pragma once
#include "IEntity.h"

struct Attributes
{
	uint32_t health;
	float movementSpeed = 2;
};

struct IActor : IEntity
{
	~IActor() {};
	virtual Attributes& getAttributes() { return m_attributes; };
	virtual void parsePacket(uint8_t* data, unsigned int length, double time);
protected:
	Attributes m_attributes;
};