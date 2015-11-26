#pragma once
#include "IActor.h"

struct Player : public IActor
{
	Player(uint32_t ID) { m_id = ID; }

	void serialize(uint8_t* array);
	int serializedSize();

	virtual void init() {}
};

