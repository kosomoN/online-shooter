#pragma once
#include "IActor.h"

class CSprite;

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
	CSprite* m_pPlayerSprite;
	CSprite* m_pFeetSprite;

private:
	glm::vec2 lastFramePos;
};
