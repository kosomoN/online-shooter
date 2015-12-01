#pragma once
#include "IActor.h"

struct CZombie : public IActor
{
	CZombie(uint32_t ID);

	virtual void update(double dt);
	virtual void serialize(uint8_t* array);
	virtual uint16_t serializedSize();

	virtual void init() {}

private:
	int m_tick;
	int m_updateDelay;
};