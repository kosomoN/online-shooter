#include "EntitySystem.h"
#include "Player.h"


CEntitySystem::~CEntitySystem()
{
	for (auto e : m_entityContainer)
		delete e.second;
}

void CEntitySystem::update()
{
	for (auto e : m_entityContainer)
	{
		if(e.second != nullptr)
			e.second->update();
	}
}

void CEntitySystem::registerEntity(IEntity* obj)
{
	m_entityContainer[obj->getID()] = obj;
	obj->init();
}
