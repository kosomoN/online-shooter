#include "Zombie.h"
#include <dayz2\NetworkConstants.h>
#include "main.h"
#include "Player.h"

CZombie::CZombie(uint32_t ID)
{
	m_id = ID;
	m_tick = 0;
	m_updateDelay = 60 + rand() % 120;
	m_type = EntityTypes::ZOMBIE;
	m_attributes.movementSpeed = 20.0f + rand() % 10;
}

void CZombie::update(double dt)
{
	if (m_attributes.pTarget)
	{
		auto dPos = m_attributes.pTarget->m_pos - m_pos;
		if(dPos.x != 0 && dPos.y != 0)
			m_pos += glm::normalize(dPos) * m_attributes.movementSpeed / 10.0f;
	}

	if (m_tick++ == m_updateDelay)
	{
		m_tick = 0;
		m_updateDelay = 60 + rand() % 120;

		float minDist = FLT_MAX;
		IEntity* closest = nullptr;
		for (ServerClient* c : gMain->clientList)
		{
			IEntity* pClientEnt = c->m_pEntity;
			auto dPos = pClientEnt->m_pos - m_pos;
			float dist = dPos.x * dPos.x + dPos.y * dPos.y;
			if (dist < minDist)
			{
				minDist = dist;
				closest = pClientEnt;
			}
		}

		if (closest != nullptr)
			m_attributes.pTarget = closest;
	}	
}

void CZombie::serialize(uint8_t * array)
{
	memcpy(array, &m_pos.x, sizeof(m_pos.x));
	memcpy(array + sizeof(m_pos.x), &m_pos.y, sizeof(m_pos.y));
}

uint16_t CZombie::serializedSize()
{
	return sizeof(m_pos.x) + sizeof(m_pos.y);
}
