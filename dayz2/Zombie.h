#pragma once

#include "IActor.h"
#include "Sprite.h"

class CZombie : public IActor
{
public:
	CZombie();
	~CZombie();

	// IEntity
	virtual void update();
	virtual void init();
	virtual void parsePacket(uint8_t* data, unsigned int length);
	// ~IEntity

private:
	CSprite* m_pZombieSprite;

};