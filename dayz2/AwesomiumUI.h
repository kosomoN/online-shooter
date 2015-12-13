#pragma once
#include <string>
#include <vector>

class CSprite;

class CAwesomiumUI
{
public:
	CAwesomiumUI();
	~CAwesomiumUI();
	CSprite* createUiObject(int width, int height, int x, int y, std::string htmlFile);
	void update();
private:
	std::vector<CSprite*> m_uiSprites;
};

