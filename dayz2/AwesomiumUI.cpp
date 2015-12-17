#include "AwesomiumUI.h"
#include "GlobalSystem.h"
#include "IUIElement.h"
#include "Sprite.h"
#include "Player.h"

CAwesomiumUI::CAwesomiumUI()
{
}

CAwesomiumUI::~CAwesomiumUI()
{
	for (IUIElement* e : m_elements)
		delete e;
}

void CAwesomiumUI::registerUIElement(IUIElement * pElem)
{
	pElem->init();
	m_elements.push_back(pElem);
}

void CAwesomiumUI::update()
{
	if (CPlayer* pPlayer = gSys->pPlayer)
	{
		for (IUIElement* e : m_elements)
		{
			glm::vec2 camPos = (gSys->pPlayer->m_pos.getLerp(gSys->pGame->gameTime));
			glm::vec2 relativePos = camPos - (gSys->pGame->camera.getSize() / 2.f);
			e->getSprite()->m_pos = relativePos;
			gSys->pSpriteBatch->drawUI(e->getSprite()->m_pos.x, e->getSprite()->m_pos.y, e->getSprite()->m_width, e->getSprite()->m_height, e->getSprite()->m_u1, e->getSprite()->m_v1, e->getSprite()->m_u2, e->getSprite()->m_v2);
		}
	}
}
