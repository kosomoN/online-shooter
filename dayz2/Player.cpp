#include "Player.h"
#include "Console.h"

CPlayer::CPlayer(uint32_t id)
{
	m_id = id;
	gSys->pEntitySystem->registerEntity(this);

	m_y = 0;
	m_x = 0;

	m_attributes.movementSpeed = 10.f;
	gSys->pConsole->registerCVar("movementSpeed", &m_attributes.movementSpeed);
}

void CPlayer::init()
{
	m_pPlayerSprite = gSys->pSpriteRenderer->addSprite(50, 50, 0, 0, 1, 1, "data/test.png");
}

void CPlayer::update()
{
	m_pPlayerSprite->m_pos = m_pos;
}

void CPlayer::parsePacket(uint8_t * data, unsigned int length)
{
	//Process other players differently
	if (this != gSys->pPlayer)
	{
		IActor::parsePacket(data, length);
	}
}
