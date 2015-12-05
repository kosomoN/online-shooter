#pragma once

#include "IInputListener.h"
#include <glm\vec2.hpp>
#include "PacketProcessor.h"
#include "NetworkConstants.h"

class CPlayer;

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
	
private:
	bool hasChanged = false;
	double lastSendTime = 0;
	uint8_t packetData[6] = { PacketTypes::INPUT_UPDATE, 0x00, 0x00, 0x00, 0x00, 0x00 };
	uint8_t m_inputSequence = 0;

};