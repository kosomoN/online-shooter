#include "Player.h"

CPlayer::CPlayer()
{
	gSys->pEntitySystem->registerEntity(this);

	m_y = 0;
	m_x = 0;

	m_attributes.movementSpeed = 0.01f;
}

void CPlayer::init()
{
	m_pPlayerSprite = gSys->pSpriteRenderer->addSprite(50, 50, 0, 0, 1, 1, 0);
	m_pPlayerSprite->m_pos = glm::vec2(200, 200);
	m_pPlayerSprite->m_rotation = 1;
}

void CPlayer::update()
{
	m_pPlayerSprite->m_rotation += 0.01;
	m_pPlayerSprite->m_pos = m_pos;
}
