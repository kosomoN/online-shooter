#include "PlayerAnimController.h"
#include "Sprite.h"
#include "GlobalSystem.h"
#include "AnimationLoader.h"
#include "Animation.h"
#include "TextureCache.h"

CPlayerAnimController::CPlayerAnimController()
{
}

CPlayerAnimController::~CPlayerAnimController()
{
}		

void CPlayerAnimController::init(std::vector<std::string>& files, CSprite* body, CSprite* feet, CSprite* shoot)
{
	m_pBody = body;
	m_pFeet = feet;
	m_pShoot = shoot;

	for (int i = 0; i < files.size();i++)
	{
		auto texture = gSys->pTextureCache->getTexture(files[i] + ".png");
		auto animation = gSys->pAnimLoader->loadAnimation(files[i] + ".anim");
		SAnimData data;
		data.anim = animation;
		data.texId = texture;
		m_animData.push_back(data);
	}

	m_lastState = IDLE;
}

void CPlayerAnimController::setState(EState state)
{
	if (m_animData[m_lastState].anim->isDone && state != m_lastState)
	{
		// Animation
		m_pFeet->m_pAnim = m_animData[state].anim;
		m_pBody->m_pAnim = m_animData[state + 1].anim;

		// Texuture
		m_pFeet->m_texture = m_animData[state].texId;
		m_pBody->m_texture = m_animData[state + 1].texId;

		// The shoot animation has a different width, so we need to modify that too.
		if (state == SHOOT)
		{
			m_pBody->m_width = m_pShoot->m_width;
			m_pBody->m_height = m_pShoot->m_height;
			m_pBody->m_rotPointOffset = m_pShoot->m_rotPointOffset;
		}
		else
		{
			m_pBody->m_width = 312 * 0.3f;
			m_pBody->m_height = 207 * 0.3f;
			m_pBody->m_rotPointOffset = glm::vec2(95.0f * 0.3f, 86.0f * 0.3f);
		}

		m_lastState = state;
	}
}
