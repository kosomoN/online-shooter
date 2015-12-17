#pragma once
#include "IActor.h"
#include "Client.h"

class b2Body;

struct Player : public IActor
{
	Player(uint32_t ID);

	virtual void update(double dt);
	virtual void hit(Player* pPlayer,float angle);
	virtual void serialize(uint8_t* array);
	virtual uint16_t serializedSize();

	virtual void init() {}

	b2Body* body;
	ServerClient* client = nullptr;
	double m_deathTime = 0.0;
	bool m_isDead = false;
};

