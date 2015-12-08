#include "Player.h"
#include "Console.h"
#include "ByteDecoder.h"
#include "GlobalSystem.h"
#include "AnimationLoader.h"
#include "Animation.h"
#include "Sprite.h"

CPlayer::CPlayer(uint32_t id)
{
	m_id = id;
	gSys->pEntitySystem->registerEntity(this);

	gSys->pConsole->registerCVar("movementSpeed", &m_attributes.movementSpeed);
}
CPlayer::~CPlayer()
{
};

void CPlayer::init()
{
	m_pFeetSprite = gSys->pSpriteRenderer->addSprite(172 * 0.3f, 124 * 0.3f, 0, 0, 1, 1, "data/survivor_walk.png");
	m_pFeetSprite->m_pAnim = gSys->pAnimLoader->loadAnimation("data/survivor_walk.anim");
	m_pFeetSprite->m_rotPointOffset = glm::vec2(86.0f * 0.3f, 62.0f * 0.3f);

	m_pFeetIdleSprite = gSys->pSpriteRenderer->addSprite(172 * 0.3f, 124 * 0.3f, 0, 0, 1, 1, "data/survivor_walk_idle.png");
	m_pFeetIdleSprite->m_rotPointOffset = glm::vec2(86.0f * 0.3f, 62.0f * 0.3f);
	m_pFeetIdleSprite->m_shouldDraw = false;

	m_pPlayerSprite = gSys->pSpriteRenderer->addSprite(312 * 0.3f, 207 * 0.3f, 0, 0, 1, 1, "data/survivor.png");
	m_pPlayerSprite->m_pAnim = gSys->pAnimLoader->loadAnimation("data/survivor.anim");
	m_pPlayerSprite->m_rotPointOffset = glm::vec2(95.0f * 0.3f, 86.0f * 0.3f);

	m_pPlayerIdleSprite = gSys->pSpriteRenderer->addSprite(312 * 0.3f, 207 * 0.3f, 0, 0, 1, 1, "data/survivor_idle.png");
	m_pPlayerIdleSprite->m_pAnim = gSys->pAnimLoader->loadAnimation("data/survivor_idle.anim");
	m_pPlayerIdleSprite->m_rotPointOffset = glm::vec2(95.0f * 0.3f, 86.0f * 0.3f);
	m_pPlayerIdleSprite->m_shouldDraw = false;
}

void CPlayer::update()
{
	glm::vec2 lerpPos = m_pos.getLerp(gSys->pGame->gameTime - 0.1);
	m_pPlayerSprite->m_pos = lerpPos - m_pPlayerSprite->m_rotPointOffset;
	m_pPlayerSprite->m_rotation = m_angle.getLerp(gSys->pGame->gameTime - 0.1);
	m_pPlayerIdleSprite->m_pos = lerpPos - m_pPlayerSprite->m_rotPointOffset;
	m_pPlayerIdleSprite->m_rotation = m_angle.getLerp(gSys->pGame->gameTime - 0.1);

	m_pFeetSprite->m_pos = lerpPos - m_pFeetSprite->m_rotPointOffset;
	m_pFeetIdleSprite->m_pos = lerpPos - m_pFeetSprite->m_rotPointOffset;
	if (abs(lerpPos.x - lastFramePos.x) > 0 || abs(lerpPos.y - lastFramePos.y) > 0)
	{
		m_pFeetSprite->m_rotation = atan2(lerpPos.y - lastFramePos.y, lerpPos.x - lastFramePos.x);
		m_pFeetIdleSprite->m_rotation = atan2(lerpPos.y - lastFramePos.y, lerpPos.x - lastFramePos.x);
	}

	if (m_oldPos == m_pos.getLerp(0))
	{
		m_pFeetIdleSprite->m_shouldDraw = true;
		m_pPlayerIdleSprite->m_shouldDraw = true;
		m_pFeetSprite->m_shouldDraw = false;
		m_pPlayerSprite->m_shouldDraw = false;
	}
	else
	{
		m_pFeetIdleSprite->m_shouldDraw = false;
		m_pPlayerIdleSprite->m_shouldDraw = false;
		m_pFeetSprite->m_shouldDraw = true;
		m_pPlayerSprite->m_shouldDraw = true;
	}

	m_oldPos = m_pos.getLerp(0);

	lastFramePos = lerpPos;
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
