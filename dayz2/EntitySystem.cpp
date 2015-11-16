#include "EntitySystem.h"
#include "Player.h"


CEntitySystem::~CEntitySystem()
{
	for (IEntity* e : m_entityContainer)
		delete e;
}

void CEntitySystem::update()
{
	for (IEntity* e : m_entityContainer)
	{
		e->update();
	}
}

void CEntitySystem::registerEntity(IEntity* obj)
{
	m_entityContainer.push_back(obj);
	obj->init();
}
