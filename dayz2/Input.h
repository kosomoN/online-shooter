#pragma once

#include "IInputListener.h"
#include <vector>

/*
USAGE:

Init or constructor:
	gSys->pInput->addListener(this);
	
	Inherit IInputListener and implement the key_callback function.
*/

class CInput
{
public:
	CInput();
	~CInput();

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void addListener(IInputListener *listener);
	void removeListener(const IInputListener* listener);
	void clearListeners();
private:
	std::vector<IInputListener*> listeners;
};