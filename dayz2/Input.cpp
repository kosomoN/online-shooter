#include "Input.h"
#include "IInputListener.h"
#include "GlobalSystem.h"
CInput::CInput() {}

CInput::~CInput(){}

void CInput::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	for (uint32_t i = 0; i < listeners.size(); i++)
		if (listeners[i]->onInputEvent(window, key, scancode, action, mods))
			return;
}

void CInput::addListener(IInputListener *listener)
{
	listeners.push_back(listener);
}

void CInput::removeListener(const IInputListener* listener)
{
	for (uint32_t i = 0; i < listeners.size(); i++)
	{
		if (listeners[i] == listener)
		{
			listeners.erase(listeners.begin() + i);
		}
	}
}

void CInput::clearListeners()
{
	listeners.clear();
}