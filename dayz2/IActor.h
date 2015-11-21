#pragma once
#include "IEntity.h"

struct Attributes
{
	float health, movementSpeed;
};

struct IActor : IEntity
{
	virtual Attributes& getAttributes() { return attributes; };

private:
	Attributes attributes;
};