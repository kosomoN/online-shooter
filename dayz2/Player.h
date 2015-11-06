#pragma once
#include "IEntity.h"
#include "IActor.h"
#include "GlobalSystem.h"

class CPlayer : public IEntity, public IActor
{
public:
	CPlayer();
	~CPlayer() {};

	// IEntiy
	virtual Vec2& getPosition() { return m_pos; };
	virtual void setPosition(Vec2& pos);
	virtual void update();
	// ~IEntity

	// IActor
	virtual void init();
	virtual IEntity* getEntity();
	virtual Attributes& getAttributes();
	// ~IActor

private:
	Vec2 m_pos;
};
