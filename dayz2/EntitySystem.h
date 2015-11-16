#pragma once
#include "IEntity.h"
#include <vector>

class CEntitySystem
{
public:
	CEntitySystem() {};
	~CEntitySystem();

	void update();
	// A new entity needs to be initialized with this. Otherwise it won't update or get deleted.
	void registerEntity(IEntity* obj);

private:
	std::vector<IEntity*> m_entityContainer;
};
