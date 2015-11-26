#pragma once
#include "IEntity.h"

struct Attributes
{
	uint32_t health;
	float movementSpeed;
};

struct IActor : IEntity
{
	virtual Attributes& getAttributes() { return m_attributes; };
protected:
	Attributes m_attributes;
};
