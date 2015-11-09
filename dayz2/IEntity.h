#pragma once

#include <glm\vec2.hpp>

// Entity interface.
struct IEntity
{
	virtual glm::vec2& getPosition() = 0;
	virtual void setPosition(glm::vec2& pos) = 0;
	virtual void update() = 0;
};