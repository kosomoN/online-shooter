#pragma once
#include "IActor.h"

class CSprite;
class CAnimation;
class CPlayerAnimController;
class b2Body;

class CPlayer : public IActor
{
public:
	CPlayer(uint32_t id);
	virtual ~CPlayer();
	// IActor
	virtual void init();
	virtual void update();
	virtual void parsePacket(uint8_t* data, unsigned int length, double time);
	// ~IActor

	void fire(float angle);

	CSprite* m_pPlayerSprite;
	CSprite* m_pFeetSprite;
	CPlayerAnimController* m_pAnimController;
	b2Body* body;

private:
	glm::vec2 m_oldPos;
};
