#include "Player.h"
#include "Console.h"

#include "ByteDecoder.h"

CPlayer::CPlayer(uint32_t id)
{
	m_id = id;
	gSys->pEntitySystem->registerEntity(this);

	m_y = 0;
	m_x = 0;

	gSys->pConsole->registerCVar("movementSpeed", &m_attributes.movementSpeed);
}

void CPlayer::init()
{
	m_pPlayerSprite = gSys->pSpriteRenderer->addSprite(50, 50, 0, 0, 1, 1, "data/survivor.png");
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
	else
	{
		if (length == 8)
		{
			glm::vec2 serverPos(readFloat(data), readFloat((data + 4)));

			float diff = (serverPos.x - m_pos.x) * (serverPos.x - m_pos.x)
				+ (serverPos.y - m_pos.y) * (serverPos.y - m_pos.y);
			
			//gSys->log(std::to_string(diff));

			//TODO Lerp small differences
			if (diff > 10 * 10)
				m_pos = serverPos;
		}
	}
}
