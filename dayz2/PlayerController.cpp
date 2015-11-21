#include "PlayerController.h"
#include "GlobalSystem.h"
#include "Player.h"

#define UP    1
#define DOWN  2
#define LEFT  4
#define RIGHT 8

CPlayerController::CPlayerController() :
m_xCoeff(0),
m_yCoeff(0)
{
	gSys->pInput->addListener(this);
}

CPlayerController::~CPlayerController()
{

}

bool CPlayerController::onInputEvent(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	// This code is horrible.
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		m_inputSequence |= UP;
		m_yCoeff = 1;
	}
	else if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		m_inputSequence |= DOWN;
		m_yCoeff = -1;
	}
	else if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		m_inputSequence |= LEFT;
		m_xCoeff = -1;
	}
	else if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		m_inputSequence |= RIGHT;
		m_xCoeff = 1;
	}


	if (key == GLFW_KEY_W && action == GLFW_RELEASE)
	{
		m_inputSequence &= ~UP;
		m_yCoeff = 0;
	}
	else if (key == GLFW_KEY_S && action == GLFW_RELEASE)
	{
		m_inputSequence &= ~DOWN;
		m_yCoeff = 0;
	}
	else if (key == GLFW_KEY_A && action == GLFW_RELEASE)
	{
		m_inputSequence &= ~LEFT;
		m_xCoeff = 0;
	}
	else if (key == GLFW_KEY_D && action == GLFW_RELEASE)
	{
		m_inputSequence &= ~RIGHT;
		m_xCoeff = 0;
	}

	return false;
}

void CPlayerController::updateMovement(CPlayer* pPlayer)
{
	float velocityY = m_yCoeff * pPlayer->getAttributes().movementSpeed;
	float velocityX = m_xCoeff * pPlayer->getAttributes().movementSpeed;
	if (pPlayer != nullptr)
		pPlayer->setPosition(pPlayer->getPosition() + glm::vec2(velocityX,velocityY));
}
