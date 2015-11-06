#include "WindowSystem.h"
#include "GlobalSystem.h"
#include <stdlib.h>
#include <stdio.h>
#include "Player.h"

CWindowSystem::~CWindowSystem()
{
	glfwTerminate();
}



void CWindowSystem::init(int x, int y)
{
	if (!glfwInit())
		return;

	m_pWin = glfwCreateWindow(x, y, "DayZ 2", NULL, NULL);
	if (!m_pWin)
	{
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(m_pWin);
}


void CWindowSystem::updateWindow()
{
	if(gSys->pEntitySystem != nullptr)
		gSys->pEntitySystem->update();
	glfwSwapBuffers(m_pWin);
	glfwPollEvents();
}
