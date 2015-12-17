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

void CPlayerAnimController::init(std::vector<std::string>& files, CSprite* body, CSprite* feet)
{
	m_pBody = body;
	m_pFeet = feet;

	for (int i = 0; i < files.size();i++)
	{
		auto animation = gSys->pAnimLoader->loadAnimation(files[i] + ".anim");
		animation->m_textureId = gSys->pTextureCache->getTexture(files[i] + ".png");
		m_animData.push_back(animation);
	}
	setState(IDLE);
}

void CPlayerAnimController::setState(EState state)
{
	if (m_animData[m_lastState+1]->isDone && state != m_lastState)
	{
		// Animation
		m_pFeet->m_pAnim = m_animData[state];
		m_pBody->m_pAnim = m_animData[state + 1];

		// Texuture
		m_pFeet->m_texture = m_animData[state]->m_textureId;
		m_pBody->m_texture = m_animData[state + 1]->m_textureId;

		// Change some size props
		m_pBody->m_width = m_animData[state + 1]->m_size.x;
		m_pBody->m_height = m_animData[state + 1]->m_size.y;
		m_pBody->m_rotPointOffset = m_animData[state + 1]->m_rotPointOffset;

		m_lastState = state;
	}
}
