#include "Player.h"
#include "Console.h"
#include "ByteDecoder.h"
#include "GlobalSystem.h"
#include "AnimationLoader.h"
#include "Animation.h"
#include "Sprite.h"
#include "PlayerAnimController.h"
#include <Box2D/Box2D.h>

CPlayer::CPlayer(uint32_t id)
{
	m_id = id;
	gSys->pEntitySystem->registerEntity(this);
	gSys->pConsole->registerCVar("movementSpeed", &m_attributes.movementSpeed);


	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 0.0f);
	bodyDef.fixedRotation = true;
	body = gSys->pb2World->CreateBody(&bodyDef);
	b2CircleShape circleShape;
	circleShape.m_radius = 0.6;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.filter.groupIndex = -1;
	body->CreateFixture(&fixtureDef);
}
CPlayer::~CPlayer()
{
	gSys->pSpriteRenderer->removeSprite(m_pFeetSprite);
	gSys->pSpriteRenderer->removeSprite(m_pPlayerSprite);
	delete m_pAnimController;
};

void CPlayer::init()
{
	float scale = 0.828f / 207.f;
	m_pFeetSprite = gSys->pSpriteRenderer->addSprite(172.f * scale, 124.f * scale, 0, 0, 1, 1, "data/survivor_walk.png");
	m_pFeetSprite->m_rotPointOffset = glm::vec2(86.0f * scale, 62.0f * scale);
	m_pFeetSprite->m_shouldDraw = false;

	m_pPlayerSprite = gSys->pSpriteRenderer->addSprite(313.f * scale, 207.f * scale, 0, 0, 1, 1, "data/survivor.png");
	m_pPlayerSprite->m_rotPointOffset = glm::vec2(95.0f * scale, 86.0f * scale);
	m_pPlayerSprite->m_shouldDraw = false;

	auto pShootSprite = gSys->pSpriteRenderer->addSprite(512 * scale, 220 * scale, 0, 0, 0, 0, "data/survivor_shoot.png");
	pShootSprite->m_rotPointOffset = glm::vec2(93 * scale, 118 * scale);
	pShootSprite->m_shouldDraw = false;

	m_pAnimController = new CPlayerAnimController;
	std::vector<string> anims = { 
		"data/survivor_walk",
		"data/survivor",
		"data/survivor_walk_idle",
		"data/survivor_idle",
		"data/survivor_walk_idle",
		"data/survivor_shoot"
	};
	m_pAnimController->init(anims, m_pPlayerSprite, m_pFeetSprite, pShootSprite);
}

void CPlayer::update()
{
	glm::vec2 lerpPos = m_pos.getLerp(gSys->pGame->gameTime - 0.1);
	m_pPlayerSprite->m_pos = lerpPos - m_pPlayerSprite->m_rotPointOffset;
	m_pPlayerSprite->m_rotation = m_angle.getLerp(gSys->pGame->gameTime - 0.1);

	m_pFeetSprite->m_pos = lerpPos - m_pFeetSprite->m_rotPointOffset;
	if (abs(lerpPos.x - lastFramePos.x) > 0 || abs(lerpPos.y - lastFramePos.y) > 0)
		m_pFeetSprite->m_rotation = atan2(lerpPos.y - lastFramePos.y, lerpPos.x - lastFramePos.x);

	if (m_oldPos == lerpPos)
		m_pAnimController->setState(EState::IDLE);
	else
		m_pAnimController->setState(EState::MOVE);	

	m_oldPos = lerpPos;

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
			
			//TODO Lerp small differences
			if (diff > 0.6f * 0.6f)
				body->SetTransform(b2Vec2(serverPos.x, serverPos.y), 0);
		}
	}
}

void CPlayer::fire(float angle)
{
	m_pAnimController->m_animData[EState::SHOOT].anim->setPlayLimit(10);
	m_pAnimController->setState(EState::SHOOT);
}
