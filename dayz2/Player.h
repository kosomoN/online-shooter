#pragma once
#include "IEntity.h"
#include "IActor.h"
#include "GlobalSystem.h"
#include "IInputListener.h"
#include <glm\vec2.hpp>

class CPlayer : public IEntity, public IActor
{
public:
	CPlayer();
	~CPlayer() {};
	// IEntiy
	virtual glm::vec2& getPosition() { return m_pos; };
	virtual void setPosition(glm::vec2& pos);
	virtual void update();
	// ~IEntity

	// IActor
	virtual void init();
	virtual IEntity* getEntity();
	virtual Attributes& getAttributes();
	// ~IActor

private:
	glm::vec2 m_pos;
};
