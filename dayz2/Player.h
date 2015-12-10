#pragma once
#include "IActor.h"

class CSprite;
class CAnimation;
class CPlayerAnimController;

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

private:
	glm::vec2 lastFramePos;
	glm::vec2 m_oldPos;
};
