#pragma once

struct GLFWwindow;

struct IInputListener
{
	virtual bool onInputEvent(GLFWwindow* window, int key, int scancode, int action, int mods) = 0;
};
