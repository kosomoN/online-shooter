#include "GlobalSystem.h"
#include "main.h"
#include "GameState.h"
#include "Console.h"

CGlobalSystem* gSys;

int main(int argc, char *argv[])
{
	CMain mw;
	if (argc > 0)
		mw.init(argv[1]);
	else
		mw.init(nullptr);
}

void CMain::init(char* host)
{
	gSys = new CGlobalSystem;
	gSys->init();

	ENetAddress address;

	if(host)
		enet_address_set_host(&address, host);
	else
		enet_address_set_host(&address, "localhost");

	address.port = 12321;
	if (!gSys->pClient->connect(address))
	{
		gSys->log("Could not connect");
		return;
	}

	gSys->pGame->init();
	gSys->pStateSystem->enterState(gSys->pGame);
	
	gSys->pConsole->registerCVar("ping", (float*)&gSys->pClient->peer->roundTripTime);

	double accumulatedTicks = 0, lastTime = glfwGetTime();
	while (!gSys->pWindowSystem->shouldClose())
	{
		gSys->pWindowSystem->updateWindow();
		gSys->pGame->frameDelta = glfwGetTime() - lastTime;
		lastTime = glfwGetTime();

		accumulatedTicks += gSys->pGame->frameDelta / TICK_LENGTH;

		if (accumulatedTicks > 10)
			accumulatedTicks = 10;

		while (accumulatedTicks >= 1)
		{
			gSys->pStateSystem->getCurrentState()->update();
			accumulatedTicks--;
		}

		gSys->pStateSystem->getCurrentState()->render();
	}

	gSys->pClient->disconnect();

	delete gSys;
	return;
}