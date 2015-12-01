#pragma once
#include <algorithm>
#include "IEntity.h"
#include <vector>

class CZSpawner
{
public:
	CZSpawner();
	~CZSpawner();


	void spawn(int ammout, uint32_t& nextId);

private:
	std::vector<IEntity*> m_zombies;
};
