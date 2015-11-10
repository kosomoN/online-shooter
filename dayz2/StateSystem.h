#pragma once

#include "IState.h"

class StateSystem
{
public:
	StateSystem() {};
	~StateSystem() {};

	void enterState(IState* pState);
	IState* getCurrentState() { return m_pCurrentState; }
private:
	IState* m_pCurrentState = nullptr;
};

