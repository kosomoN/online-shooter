#pragma once
#include "IEntity.h"

struct Attributes
{
	float health, movementSpeed;
};

struct IActor : IEntity
{
	Attributes& getAttributes() { return attributes; };

private:
	Attributes attributes;
};