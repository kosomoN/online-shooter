#pragma once

#include "Vec2.h"

// Entity interface.
struct IEntity
{
	virtual Vec2& getPosition() = 0;
	virtual void setPosition(Vec2& pos) = 0;
	virtual void update() = 0;
};