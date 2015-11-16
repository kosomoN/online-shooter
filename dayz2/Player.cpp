#include "Player.h"

CPlayer::CPlayer()
{
	gSys->pEntitySystem->registerEntity(this);
	gSys->pInput->addListener(this);

	m_y = 0;
	m_x = 0;
}

void CPlayer::init()
{
	m_pPlayerSprite = gSys->pSpriteRenderer->addSprite(50, 50, 0, 0, 1, 1, 0);
	m_pPlayerSprite->m_pos = glm::vec2(200, 200);
}

void CPlayer::update()
{
	m_pPlayerSprite->m_pos += glm::vec2(m_x, m_y);
}

bool CPlayer::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{


	// This code is horrible.
	if (key == GLFW_KEY_W && action != GLFW_RELEASE)
		m_y = 1;
	else if (key == GLFW_KEY_S && action != GLFW_RELEASE)
		m_y = -1;
	else if (key == GLFW_KEY_A && action != GLFW_RELEASE)
		m_x = -1;
	else if (key == GLFW_KEY_D && action != GLFW_RELEASE)
		m_x = 1;

	if (key == GLFW_KEY_W ||
		key == GLFW_KEY_A ||
		key == GLFW_KEY_S ||
		key == GLFW_KEY_D)
	{
		if (action == GLFW_RELEASE)
		{
			m_x = 0;
			m_y = 0;
		}
	}
		


	return false;
}
