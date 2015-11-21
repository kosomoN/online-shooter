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
	void updateMovement(CPlayer * pEnt);
	//~IInput
	
private:
	int m_xCoeff, m_yCoeff;
	uint8_t m_inputSequence = 0;

};