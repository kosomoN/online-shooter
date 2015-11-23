#pragma once
#include "IEntity.h"
#include "IActor.h"
#include "GlobalSystem.h"
#include "IInputListener.h"
#include <glm\vec2.hpp>
#include "PlayerController.h"

class CPlayer : public IActor
{
public:
	CPlayer(uint32_t id);
	~CPlayer() {};

	// IActor
	virtual void init();
	virtual void update();
	virtual void parsePacket(uint8_t* data, unsigned int length);
	// ~IActor

private:
	CSprite* m_pPlayerSprite;
	int m_x, m_y;
};
