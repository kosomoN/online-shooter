#include "Player.h"

void Player::serialize(uint8_t * array)
{
	memcpy(array, &m_pos.x, sizeof(m_pos.x));
	memcpy(array + sizeof(m_pos.x), &m_pos.y, sizeof(m_pos.y));
}

int Player::serializedSize()
{
	return sizeof(m_pos.x) + sizeof(m_pos.y);
}
