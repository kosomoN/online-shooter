#include "SpriteRenderer.h"
#include <algorithm>
#include "GlobalSystem.h"

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

void SpriteRenderer::registerSprite(Sprite* pSprite)
{
	m_sprites.push_back(pSprite);
}

void SpriteRenderer::removeSprite(Sprite * pSprite)
{
	m_sprites.erase(std::remove(m_sprites.begin(), m_sprites.end(), pSprite));
}
