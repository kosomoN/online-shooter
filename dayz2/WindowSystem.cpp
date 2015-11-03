#include "WindowSystem.h"
#include "GlobalSystem.h"
#include <stdlib.h>
#include <stdio.h>

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
	glfwSwapBuffers(m_pWin);
	glfwPollEvents();
}
