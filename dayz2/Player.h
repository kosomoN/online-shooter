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
	CPlayer();
	~CPlayer() {};

	// IActor
	virtual void init();
	virtual void update();
	virtual const glm::vec2& getPosition() { return m_pos; }
	virtual void setPosition(const glm::vec2& pos) { m_pos = pos; }
	virtual Attributes& getAttributes() { return m_attributes; };
	// ~IActor

private:
	Attributes m_attributes;
	glm::vec2 m_pos;
	CSprite* m_pPlayerSprite;
	int m_x, m_y;
};
