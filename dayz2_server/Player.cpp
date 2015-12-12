#include "Player.h"

#include "dayz2/NetworkConstants.h"
#include <iostream>
#include "main.h"
#include <Box2D/Box2D.h>

Player::Player(uint32_t ID)
{
	m_id = ID;
	m_type = EntityTypes::PLAYER;
	m_width = 42;
	m_height = 42;
	gMain->initializeEntityOnClients(this);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 0.0f);
	bodyDef.fixedRotation = true;
	body = gMain->pWorld->CreateBody(&bodyDef);
	b2CircleShape circleShape;
	circleShape.m_radius = 0.6;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.filter.groupIndex = -1;
	body->CreateFixture(&fixtureDef);
}

void Player::update(double dt)
{
	glm::vec2 velocity = glm::vec2(0);

	if ((client->keyStates >> RIGHT_KEY) & 1)
		velocity.x += getAttributes().movementSpeed;

	if ((client->keyStates >> LEFT_KEY) & 1)
		velocity.x -= getAttributes().movementSpeed;

	if ((client->keyStates >> UP_KEY) & 1)
		velocity.y += getAttributes().movementSpeed;

	if ((client->keyStates >> DOWN_KEY) & 1)
		velocity.y -= getAttributes().movementSpeed;

	if (abs(velocity.x) > 0 && abs(velocity.y) > 0)
		velocity *= sqrt(0.5);

	body->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
	b2Vec2 pos = body->GetPosition();
	m_pos.x = pos.x;
	m_pos.y = pos.y;
}

void Player::hit(Player * pPlayer)
{
	m_attributes.health -= 20;
}

void Player::serialize(uint8_t * array)
{
	memcpy(array, &m_pos.x, sizeof(m_pos.x));
	memcpy(array + sizeof(m_pos.x), &m_pos.y, sizeof(m_pos.y));
	memcpy(array + sizeof(m_pos.x) + sizeof(m_pos.y), &m_angle, sizeof(m_angle));
}

uint16_t Player::serializedSize()
{
	return sizeof(m_pos.x) + sizeof(m_pos.y) + sizeof(m_angle);
}
