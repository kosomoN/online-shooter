#include "Zombie.h"
#include <dayz2\NetworkConstants.h>

CZombie::CZombie(uint32_t ID)
{
	m_id = ID;
	m_type = EntityTypes::ZOMBIE;
}
float a = 0;
void CZombie::update(double dt)
{
	a += 2 * dt;
	m_pos.x = 100 * cos(a);
	m_pos.y = 100 * sin(a);
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
