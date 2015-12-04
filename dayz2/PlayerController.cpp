#include "PlayerController.h"
#include "GlobalSystem.h"
#include "Player.h"
#include "Client.h"
#include "NetworkConstants.h"

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
		m_inputSequence |= 1 << UP_KEY;
	else if (key == GLFW_KEY_S && action == GLFW_PRESS)
		m_inputSequence |= 1 << DOWN_KEY;
	else if (key == GLFW_KEY_A && action == GLFW_PRESS)
		m_inputSequence |= 1 << LEFT_KEY;
	else if (key == GLFW_KEY_D && action == GLFW_PRESS)
		m_inputSequence |= 1 << RIGHT_KEY;


	if (key == GLFW_KEY_W && action == GLFW_RELEASE)
		m_inputSequence &= ~(1 << UP_KEY);
	else if (key == GLFW_KEY_S && action == GLFW_RELEASE)
		m_inputSequence &= ~(1 << DOWN_KEY);
	else if (key == GLFW_KEY_A && action == GLFW_RELEASE)
		m_inputSequence &= ~(1 << LEFT_KEY);
	else if (key == GLFW_KEY_D && action == GLFW_RELEASE)
		m_inputSequence &= ~(1 << RIGHT_KEY);

	if (oldInput != m_inputSequence)
		hasChanged = true;

	return false;
}

void CPlayerController::updateMovement()
{
	glm::vec2 velocity;

	CPlayer* pPlayer = gSys->pPlayer;

	if ((m_inputSequence >> RIGHT_KEY) & 1)
		velocity.x += gSys->pGame->frameDelta * pPlayer->getAttributes().movementSpeed;

	if ((m_inputSequence >> LEFT_KEY) & 1)
		velocity.x -= gSys->pGame->frameDelta * pPlayer->getAttributes().movementSpeed;

	if ((m_inputSequence >> UP_KEY) & 1)
		velocity.y += gSys->pGame->frameDelta * pPlayer->getAttributes().movementSpeed;

	if ((m_inputSequence >> DOWN_KEY) & 1)
		velocity.y -= gSys->pGame->frameDelta * pPlayer->getAttributes().movementSpeed;

	if (abs(velocity.x) > 0 && abs(velocity.y) > 0)
		velocity *= sqrt(0.5);

	double xpos, ypos;
	glfwGetCursorPos(gSys->pWindowSystem->getWindowPtr(), &xpos, &ypos);
	glm::vec2 rotPointOffser = glm::vec2(pPlayer->m_pPlayerSprite->m_width, pPlayer->m_pPlayerSprite->m_height) * pPlayer->m_pPlayerSprite->m_rotPointOffset;
	m_point = glm::vec2(gSys->pGame->camera.getPosition().x, gSys->pGame->camera.getPosition().y)- rotPointOffser - (glm::vec2(gSys->pGame->camera.getSize().x / 2.0f, gSys->pGame->camera.getSize().y / 2)) + glm::vec2(xpos, ypos);
	double angle = atan2((double)pPlayer->m_pos.getLerp(0).x - (double)m_point.x, (double)pPlayer->m_pos.getLerp(0).y - (double)m_point.y) + 3.14 / 2;
	pPlayer->m_angle = angle;

	pPlayer->m_pos.addValue(pPlayer->m_pos.getLerp(0) + velocity, 0);
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

	anglePacket[0] = PacketTypes::INPUT_UPDATE;
	memcpy(anglePacket + 1, &gSys->pPlayer->m_angle, sizeof(float));
	ENetPacket* packet = enet_packet_create(anglePacket, sizeof(anglePacket), ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(gSys->pClient->peer, SNAPSHOT_CHANNEL, packet);
}
