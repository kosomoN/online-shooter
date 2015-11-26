#pragma once

#include <vector>
#include "Sprite.h"
#include <string>

class CSpriteRenderer
{
public:
	CSpriteRenderer() {};
	~CSpriteRenderer();

	void renderSprites();
	void removeSprite(CSprite* pSprite);
	CSprite* addSprite(int width, int height, float u1, float v1, float u2, float v2, std::string texture);
private:
	std::vector<CSprite*> m_sprites;
	
};

