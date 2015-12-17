#include "Player.h"

#include "dayz2/NetworkConstants.h"
#include <iostream>
#include "main.h"
#include <Box2D/Box2D.h>

Player::Player(uint32_t ID)
{
	m_id = ID;
	m_type = EntityTypes::PLAYER;
	m_width = 10;
	m_height = 10;
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

	body->SetLinearVelocity(b2Vec2(0, 0));
	m_pos = glm::vec2(rand() % 50, rand() % 50);
	body->SetTransform(b2Vec2(m_pos.x, m_pos.y), m_angle);
}

void Player::update(double dt)
{
	if (m_isDead)
		m_deathTime += dt;

	printf("%b \n", m_isDead);
	if (m_isDead && m_deathTime >= 2.0)
	{
		body->SetLinearVelocity(b2Vec2(0,0));
		m_pos = glm::vec2(rand() % 50, rand() % 50);
		body->SetTransform(b2Vec2(m_pos.x, m_pos.y), m_angle);
		m_isDead = false;
		m_deathTime = 0.0;
		m_attributes.health = 100;
	}
	else
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
}

void Player::hit(Player* pPlayer, float angle)
{
	if (m_attributes.health < 20)
		m_isDead = true;
	else
		m_attributes.health -= 20;

	uint8_t packetData[9];
	packetData[0] = PacketTypes::PLAYER_HIT;
	memcpy(packetData + 1, &m_id, sizeof(m_id));
	memcpy(packetData + 5, &angle, sizeof(float));
	ENetPacket* packet = enet_packet_create(packetData, sizeof(packetData), 0);
	enet_host_broadcast(gMain->server, EFFECTS_CHANNEL, packet);
}

void Player::serialize(uint8_t * array)
{
	memcpy(array, &m_pos.x, sizeof(m_pos.x));
	memcpy(array + sizeof(m_pos.x), &m_pos.y, sizeof(m_pos.y));
	memcpy(array + sizeof(m_pos.x) + sizeof(m_pos.y), &m_angle, sizeof(m_angle));
	memcpy(array + sizeof(m_pos.x) + sizeof(m_pos.y) + sizeof(m_angle), &m_attributes.health, sizeof(m_attributes.health));
}

uint16_t Player::serializedSize()
{
	return sizeof(m_pos.x) + sizeof(m_pos.y) + sizeof(m_angle) + sizeof(m_attributes.health);
}
