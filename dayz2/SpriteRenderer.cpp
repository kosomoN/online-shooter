#include "SpriteRenderer.h"
#include <algorithm>
#include "GlobalSystem.h"

SpriteRenderer::~SpriteRenderer()
{
	for (Sprite* s : m_sprites)
		delete s;
}

void SpriteRenderer::renderSprites()
{
	if (m_sprites.size() > 0)
	{
		SpriteBatch* sb = gSys->pSpriteBatch;
		sb->begin(m_sprites.front()->m_texture);

		for (auto i = m_sprites.begin(); i < m_sprites.end(); i++)
		{
			if ((*i)->m_texture != sb->getCurrentTexture())
				sb->begin((*i)->m_texture);

			sb->draw((*i));
		}

		sb->end();
	}
}

void SpriteRenderer::removeSprite(Sprite * pSprite)
{
	m_sprites.erase(std::remove(m_sprites.begin(), m_sprites.end(), pSprite));
}

Sprite* SpriteRenderer::addSprite(int width, int height, float u1, float v1, float u2, float v2, GLuint texture)
{
	auto pSprite = new Sprite(width, height, u1, v1, u2, v2, texture);
	m_sprites.push_back(pSprite);
	return pSprite;
}

