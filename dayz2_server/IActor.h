#pragma once
#include "IEntity.h"

struct Attributes
{
	uint32_t health = 100;
	float movementSpeed = 100;
	IEntity* pTarget = nullptr;
};

struct IActor : IEntity
{
	virtual Attributes& getAttributes() { return m_attributes; };
protected:
	Attributes m_attributes;
};
