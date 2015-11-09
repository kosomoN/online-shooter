#include "Player.h"

CPlayer::CPlayer()
{
	gSys->pEntitySystem->registerEntity(this);
}

void CPlayer::setPosition(glm::vec2& pos)
{
	m_pos = pos;
}

void CPlayer::update()
{
}

void CPlayer::init()
{
}

IEntity* CPlayer::getEntity()
{
	return static_cast<IEntity*>(this);
}

Attributes& CPlayer::getAttributes()
{
	return Attributes();
}
