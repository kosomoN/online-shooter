#pragma once
#include "IEntity.h"

struct Attributes
{
	float health, movementSpeed;
};

struct IActor
{
	virtual void init() = 0;
	virtual IEntity* getEntity() = 0;
	virtual Attributes& getAttributes() = 0;
};