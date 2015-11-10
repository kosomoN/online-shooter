#include "StateSystem.h"

void StateSystem::enterState(IState* pState)
{
	if (m_pCurrentState != nullptr)
	{
		m_pCurrentState->exit();
	}
	m_pCurrentState = pState;
}
