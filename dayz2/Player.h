#pragma once
#include "IEntity.h"
#include "IActor.h"
#include "GlobalSystem.h"
#include "IInputListener.h"
#include <glm\vec2.hpp>

class CPlayer : public IActor
{
public:
	CPlayer();
	~CPlayer() {};

	virtual void init();
};
