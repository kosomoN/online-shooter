#include "Player.h"

#include "dayz2/NetworkConstants.h"
#include <iostream>

Player::Player(uint32_t ID)
{
	m_id = ID;
	m_type = EntityTypes::PLAYER;
}

void Player::update(double dt)
{
	glm::vec2 velocity = glm::vec2(0);

	if ((client->keyStates >> RIGHT_KEY) & 1)
		velocity.x += dt * getAttributes().movementSpeed;

	if ((client->keyStates >> LEFT_KEY) & 1)
		velocity.x -= dt * getAttributes().movementSpeed;

	if ((client->keyStates >> UP_KEY) & 1)
		velocity.y += dt * getAttributes().movementSpeed;

	if ((client->keyStates >> DOWN_KEY) & 1)
		velocity.y -= dt * getAttributes().movementSpeed;

	if (abs(velocity.x) > 0 && abs(velocity.y) > 0)
		velocity *= sqrt(0.5);

	m_pos += velocity;
}

void Player::serialize(uint8_t * array)
{
	memcpy(array, &m_pos.x, sizeof(m_pos.x));
	memcpy(array + sizeof(m_pos.x), &m_pos.y, sizeof(m_pos.y));
}

uint16_t Player::serializedSize()
{
	return sizeof(m_pos.x) + sizeof(m_pos.y);
}
