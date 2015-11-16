#pragma once

#include "IState.h"

class CStateSystem
{
public:
	CStateSystem() {};
	~CStateSystem() {};

	void enterState(IState* pState);
	IState* getCurrentState() { return m_pCurrentState; }
private:
	IState* m_pCurrentState = nullptr;
};

