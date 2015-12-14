#pragma once
#include <string>
#include <vector>

class CSprite;
struct IUIElement;

class CAwesomiumUI
{
public:
	CAwesomiumUI();
	~CAwesomiumUI();
	void registerUIElement(IUIElement* pElem);
	void update();
	std::vector<IUIElement*> m_elements;
};

