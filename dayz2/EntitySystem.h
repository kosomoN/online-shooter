#pragma once
#include "IEntity.h"
#include <vector>
#include <unordered_map>

class CEntitySystem
{
public:
	CEntitySystem() {};
	~CEntitySystem();

	void update();
	// A new entity needs to be initialized with this. Otherwise it won't update or get deleted.
	void registerEntity(IEntity* obj);
	void deleteEntity(IEntity* obj);
	IEntity* getEntity(uint32_t id) { return m_entityContainer[id]; }

private:
	std::unordered_map<uint32_t, IEntity*> m_entityContainer;
};
