#pragma once

#include "IInputListener.h"
#include <glm\vec2.hpp>
#include "PacketProcessor.h"
#include "NetworkConstants.h"

class CPlayer;
class b2Body;

#define MAX_INPUT_SEND_RATE 128

class CPlayerController : public IInputListener
{
public:
	CPlayerController();
	~CPlayerController();

	// IInput
	virtual bool onInputEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
	//~IInput

	void updateMovement();
	uint8_t& getInputSequence() { return m_inputSequence; }
	void sendInput();
	void mouseButtonCallback(int button, int action, int mods);

	
private:
	float calculateRotation();
	bool hasChanged = false;
	double lastSendTime = 0;
	uint8_t packetData[6] = { PacketTypes::INPUT_UPDATE, 0x00, 0x00, 0x00, 0x00, 0x00 };
	uint8_t shootPacketData[5] = { PacketTypes::PLAYER_SHOOT, 0x00, 0x00, 0x00, 0x00 };
	uint8_t m_inputSequence = 0;
};