#include "PlayerController.h"
#include "GlobalSystem.h"
#include "Player.h"
#include "Client.h"
#include "NetworkConstants.h"
#include <glm\common.hpp>
#include "PlayerAnimController.h"

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	gSys->pPlayerController->mouseButtonCallback(button, action, mods);
}

CPlayerController::CPlayerController()
{
	gSys->pInput->addListener(this);

	glfwSetMouseButtonCallback(gSys->pWindowSystem->getWindowPtr(), mouse_button_callback);
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

	pPlayer->m_pos.addValue(pPlayer->m_pos.getLerp(0) + velocity, 0);

	float oldAngle = pPlayer->m_angle.getLerp(0);
	double finalAngle = calculateRotation();
	pPlayer->m_angle.addValue(finalAngle, 0);

	if (oldAngle != finalAngle)
		hasChanged = true;
}

void CPlayerController::sendInput()
{
	if (hasChanged && glfwGetTime() - lastSendTime > 1.0 / MAX_INPUT_SEND_RATE)
	{
		packetData[1] = m_inputSequence;
		memcpy(packetData + 2, &gSys->pPlayer->m_angle, sizeof(float));
		ENetPacket* packet = enet_packet_create(packetData, sizeof(packetData), ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(gSys->pClient->peer, SNAPSHOT_CHANNEL, packet);
		hasChanged = false;
		lastSendTime = glfwGetTime();
	}
}

void CPlayerController::mouseButtonCallback(int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double angle = calculateRotation();
		gSys->pPlayer->fire(angle);

		float floatAngle = (float)angle;
		memcpy(shootPacketData + 1, &floatAngle, sizeof(float));
		ENetPacket* shootPacket = enet_packet_create(shootPacketData, sizeof(shootPacketData), ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(gSys->pClient->peer, COMMAND_CHANNEL, shootPacket);
	}
}

float CPlayerController::calculateRotation()
{
	double xpos, ypos;
	glfwGetCursorPos(gSys->pWindowSystem->getWindowPtr(), &xpos, &ypos);
	int width, height;
	glfwGetWindowSize(gSys->pWindowSystem->getWindowPtr(), &width, &height);

	xpos /= width;
	ypos /= height;

	xpos *= gSys->pGame->camera.getSize().x;
	ypos *= gSys->pGame->camera.getSize().y;

	glm::vec2 rotPointOffset = gSys->pPlayer->m_pPlayerSprite->m_rotPointOffset;
	glm::vec2 mousePoint = glm::vec2(gSys->pGame->camera.getPosition().x, gSys->pGame->camera.getPosition().y)
				- (glm::vec2(gSys->pGame->camera.getSize().x / 2.0f, -gSys->pGame->camera.getSize().y / 2))
				+ glm::vec2(xpos, -ypos);



	double radius = 33 * 0.3;
	glm::vec2 playerToMouse = mousePoint - gSys->pPlayer->m_pos.getLerp(0);
	double playerMouseLength = glm::length(playerToMouse);
	if (playerMouseLength < radius)
		return atan2(playerToMouse.y, playerToMouse.x) + 3.14 / 2;

	double angle = asin(radius / playerMouseLength);

	float rotX = (float)(playerToMouse.x * cos(angle) - playerToMouse.y * sin(angle));
	float rotY = (float)(playerToMouse.x * sin(angle) + playerToMouse.y * cos(angle));
	glm::vec2 rotNorm(rotX, rotY);
	rotNorm /= glm::length(rotNorm);

	double sideLength = sqrt(playerMouseLength * playerMouseLength - radius * radius);
	double x = rotNorm.x * sideLength;
	double y = rotNorm.y * sideLength;

	return atan2(y, x);
}
