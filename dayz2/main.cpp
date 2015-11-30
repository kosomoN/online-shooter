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

	gSys->pGame->init();
	gSys->pStateSystem->enterState(gSys->pGame);
	
	double dt, lastTime = glfwGetTime();
	while (!gSys->pWindowSystem->shouldClose())
	{
		gSys->pWindowSystem->updateWindow();
		dt = glfwGetTime() - lastTime;
		lastTime = glfwGetTime();

		if (fmod(gSys->pGame->gameTime, 1.0) < dt)
			gSys->log("Ping: " + std::to_string(gSys->pClient->peer->roundTripTime));

		gSys->pStateSystem->getCurrentState()->update(dt);
		gSys->pStateSystem->getCurrentState()->render();
	}

	gSys->pClient->disconnect();

	delete gSys;
	return;
}