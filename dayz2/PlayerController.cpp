#include "PlayerController.h"
#include "GlobalSystem.h"
#include "Player.h"
#include "Client.h"

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
	uint8_t oldInput = m_inputSequence;
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

	if (oldInput != m_inputSequence)
		hasChanged = true;

	return false;
}

void CPlayerController::updateMovement()
{
	float velocityY = m_yCoeff * gSys->pPlayer->getAttributes().movementSpeed;
	float velocityX = m_xCoeff * gSys->pPlayer->getAttributes().movementSpeed;
	if (gSys->pPlayer != nullptr)
		gSys->pPlayer->setPosition(gSys->pPlayer->getPosition() + glm::vec2(velocityX,velocityY));
}

void CPlayerController::sendInput()
{
	if (hasChanged && glfwGetTime() - lastSendTime > 1.0 / MAX_INPUT_SEND_RATE)
	{
		packetData[1] = m_inputSequence;
		ENetPacket* packet = enet_packet_create(packetData, sizeof(packetData), ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(gSys->pClient->peer, SNAPSHOT_CHANNEL, packet);
		hasChanged = false;
		lastSendTime = glfwGetTime();
	}
}
