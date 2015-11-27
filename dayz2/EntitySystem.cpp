#include "EntitySystem.h"
#include "Player.h"


CEntitySystem::~CEntitySystem()
{
	for (std::pair<uint32_t, IEntity*> e : m_entityContainer)
	{
		delete e.second;
	}
}

void CEntitySystem::update()
{
	for (std::pair<uint32_t, IEntity*> e : m_entityContainer)
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

void CEntitySystem::deleteEntity(IEntity* obj)
{
	m_entityContainer.erase(m_entityContainer.find(obj->getID()));
	delete obj;
}
