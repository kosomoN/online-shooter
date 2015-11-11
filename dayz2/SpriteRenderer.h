#pragma once

#include <vector>
#include "Sprite.h"

class SpriteRenderer
{
public:
	SpriteRenderer() {};
	~SpriteRenderer();

	void renderSprites();
	void removeSprite(Sprite* pSprite);
	Sprite* addSprite(int width, int height, float u1, float v1, float u2, float v2, GLuint texture);
private:
	std::vector<Sprite*> m_sprites;
	
};

