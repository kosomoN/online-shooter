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

	m_pBody->m_shouldDraw = true;
	m_pFeet->m_shouldDraw = true;
}

void CPlayerAnimController::setState(EState state)
{
	// Animation
	m_pFeet->m_pAnim = m_animData[state].anim;
	m_pBody->m_pAnim = m_animData[state+2].anim;

	// Texuture
	m_pFeet->m_texture = m_animData[state].texId;
	m_pBody->m_texture = m_animData[state+2].texId;
}
