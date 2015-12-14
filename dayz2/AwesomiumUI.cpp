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
			glm::vec2 relativePos = pPlayer->m_pos.getLerp(gSys->pGame->gameTime - 0.1) - (gSys->pGame->camera.getSize() / 2.f);
			e->getSprite()->m_pos = relativePos;
		}
	}
}
