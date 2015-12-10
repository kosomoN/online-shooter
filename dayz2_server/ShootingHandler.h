#pragma once

#include "Player.h"

class CShootingHandler
{
public:
	CShootingHandler();
	~CShootingHandler();

	void fire(Player* pClient, float shootingAngle);
};

