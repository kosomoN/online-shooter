#pragma once
#include "IActor.h"
#include "Client.h"

struct Player : public IActor
{
	Player(uint32_t ID);

	virtual void update(double dt);
	virtual void serialize(uint8_t* array);
	virtual uint16_t serializedSize();

	virtual void init() {}

	ServerClient* client = nullptr;
};

