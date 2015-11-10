#pragma once

#include <vector>
#include "Sprite.h"

class SpriteRenderer
{
public:
	SpriteRenderer() {};
	~SpriteRenderer() {};

	void renderSprites();
	void registerSprite(Sprite* pSprite);
	void removeSprite(Sprite* pSprite);
private:
	std::vector<Sprite*> m_sprites;
	
};

