#include "ZSpawner.h"
#include "Zombie.h"
#include "main.h"
#include "Player.h"
#include <dayz2\NetworkConstants.h>
#include <cfloat>

void CZSpawner::spawn(int ammount, uint32_t& nextId)
{
	for (int i = 0; i < ammount; i++)
	{
		auto z = new CZombie(nextId++);
		z->getAttributes().pTarget = nullptr;
		gMain->entityList.push_back(z);
	}
}

CZSpawner::CZSpawner() 
{
}

CZSpawner::~CZSpawner()
{
}
