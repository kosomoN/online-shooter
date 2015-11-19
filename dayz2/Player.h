#pragma once
#include "IEntity.h"
#include "IActor.h"
#include "GlobalSystem.h"
#include "IInputListener.h"
#include <glm\vec2.hpp>

class CPlayer : public IActor, public IInputListener
{
public:
	CPlayer(uint32_t id);
	~CPlayer() {};

	// IActor
	virtual void init();
	virtual void update();
	// ~IActor

	// IInput
	virtual bool key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	// ~IInput

private:
	CSprite* m_pPlayerSprite;
	int m_x, m_y;
};
