#include "GlobalSystem.h"
#include "main.h"
#include "GameState.h"

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

	ENetAddress address;
	enet_address_set_host(&address, "localhost");
	address.port = 12321;
	if (!gSys->pClient->connect(address))
	{
		gSys->log("Could not connect");
		return;
	}

	CGameState* gameState = new CGameState();
	gameState->init();
	gSys->pStateSystem->enterState(gameState);
	
	double dt, lastTime = glfwGetTime();
	while (!gSys->pWindowSystem->shouldClose())
	{
		gSys->pWindowSystem->updateWindow();
		dt = glfwGetTime() - lastTime;
		lastTime = glfwGetTime();

		gSys->pStateSystem->getCurrentState()->update(dt);
		gSys->pStateSystem->getCurrentState()->render();
	}

	delete gameState;
	delete gSys;
	return;
}