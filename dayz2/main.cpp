#include <GL\glew.h>
#include <GL\GL.h>
#include <GLFW\glfw3.h>
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "GlobalSystem.h"
#include "main.h"

CGlobalSystem* gSys;

int main(void)
{
	CMain mw;
	mw.init();
}

void CMain::init()
{
	gSys = new CGlobalSystem;
	gSys->init();

	while (!gSys->pWindowSystem->shouldClose())
	{
		gSys->pWindowSystem->updateWindow();
	}
	delete gSys;
	return;
}