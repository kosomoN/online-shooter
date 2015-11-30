#include "Zombie.h"
#include "GlobalSystem.h"
#include "SpriteRenderer.h"
#include "Sprite.h"

CZombie::CZombie(uint32_t entId)
{
	m_id = entId;
	gSys->pEntitySystem->registerEntity(this);
}

CZombie::~CZombie()
{
}

void CZombie::init()
{
	m_attributes.movementSpeed = 50;
	m_pZombieSprite = gSys->pSpriteRenderer->addSprite(50, 50, 0, 0, 1, 1, "data/Kappa.png");
}

void CZombie::update()
{
	m_pZombieSprite->m_pos = m_pos.getLerp(gSys->pGame->gameTime - 0.1);
}

void CZombie::parsePacket(uint8_t * data, unsigned int length, double time)
{
	IActor::parsePacket(data, length, time);
}
