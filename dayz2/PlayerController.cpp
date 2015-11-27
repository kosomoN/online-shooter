#include "PlayerController.h"
#include "GlobalSystem.h"
#include "Player.h"
#include "Client.h"

#include <iostream>

#define UP_KEY    0
#define DOWN_KEY  1
#define LEFT_KEY  2
#define RIGHT_KEY 3

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
		m_inputSequence |= 1 << UP_KEY;
		m_yCoeff = 1;
	}
	else if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		m_inputSequence |= 1 << DOWN_KEY;
		m_yCoeff = -1;
	}
	else if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		m_inputSequence |= 1 << LEFT_KEY;
		m_xCoeff = -1;
	}
	else if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		m_inputSequence |= 1 << RIGHT_KEY;
		m_xCoeff = 1;
	}


	if (key == GLFW_KEY_W && action == GLFW_RELEASE)
	{
		m_inputSequence &= ~(1 << UP_KEY);
		m_yCoeff = 0;
	}
	else if (key == GLFW_KEY_S && action == GLFW_RELEASE)
	{
		m_inputSequence &= ~(1 << DOWN_KEY);
		m_yCoeff = 0;
	}
	else if (key == GLFW_KEY_A && action == GLFW_RELEASE)
	{
		m_inputSequence &= ~(1 << LEFT_KEY);
		m_xCoeff = 0;
	}
	else if (key == GLFW_KEY_D && action == GLFW_RELEASE)
	{
		m_inputSequence &= ~(1 << RIGHT_KEY);
		m_xCoeff = 0;
	}

	if (oldInput != m_inputSequence)
		hasChanged = true;

	return false;
}

void CPlayerController::updateMovement(double dt)
{
	glm::vec2 velocity = glm::vec2(0);

	CPlayer* pPlayer = gSys->pPlayer;

	if ((m_inputSequence >> RIGHT_KEY) & 1)
		velocity.x += dt * pPlayer->getAttributes().movementSpeed;

	if ((m_inputSequence >> LEFT_KEY) & 1)
		velocity.x -= dt * pPlayer->getAttributes().movementSpeed;

	if ((m_inputSequence >> UP_KEY) & 1)
		velocity.y += dt * pPlayer->getAttributes().movementSpeed;

	if ((m_inputSequence >> DOWN_KEY) & 1)
		velocity.y -= dt * pPlayer->getAttributes().movementSpeed;

	if (gSys->pPlayer != nullptr)
		gSys->pPlayer->setPosition(gSys->pPlayer->getPosition() + velocity);
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
