#include "Player.h"
#include "Console.h"
#include "ByteDecoder.h"
#include "GlobalSystem.h"
#include "AnimationLoader.h"

CPlayer::CPlayer(uint32_t id)
{
	m_id = id;
	gSys->pEntitySystem->registerEntity(this);

	gSys->pConsole->registerCVar("movementSpeed", &m_attributes.movementSpeed);
}
CPlayer::~CPlayer()
{
	gSys->pSpriteRenderer->removeSprite(m_pPlayerSprite);
};

void CPlayer::init()
{
	m_pPlayerSprite = gSys->pSpriteRenderer->addSprite(312 * 0.3f, 207 * 0.3f, 0, 0, 1, 1, "data/survivor.png");
	m_pPlayerSprite->m_pAnim = gSys->pAnimLoader->loadAnimation("data/survivor.anim");
	m_pPlayerSprite->m_rotPointOffset = glm::vec2(95.0f/313.f, 120.0f/206.f);

}

void CPlayer::update()
{
	m_pPlayerSprite->m_pos = m_pos.getLerp(gSys->pGame->gameTime - 0.1);
	m_pPlayerSprite->m_rotation = m_angle;
}

void CPlayer::parsePacket(uint8_t * data, unsigned int length, double time)
{
	//Process other players differently
	if (this != gSys->pPlayer)
	{
		IActor::parsePacket(data, length, time);
	}
	else
	{
		if (length == 12)
		{
			glm::vec2 serverPos(readFloat(data), readFloat((data + 4)));
			glm::vec2 clientPos = m_pos.getLerp(0);

			float diff = (serverPos.x - clientPos.x) * (serverPos.x - clientPos.x)
				+ (serverPos.y - clientPos.y) * (serverPos.y - clientPos.y);
			
			//gSys->log(std::to_string(diff));

			//TODO Lerp small differences
			if (diff > 10 * 10)
				m_pos.addValue(serverPos, 0);
		}
	}
}
