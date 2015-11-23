#pragma once

#include "IInputListener.h"
#include <glm\vec2.hpp>
class CPlayer;

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
	
private:
	int m_xCoeff, m_yCoeff;
	uint8_t m_inputSequence = 0;

};