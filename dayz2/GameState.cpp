#include "GameState.h"

#include "GlobalSystem.h"
#include "lodepng.h"
#include "Console.h"
#include "Zombie.h"
#include <vector>

CGameState::~CGameState()
{
}

void CGameState::init()
{
}

void CGameState::render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shader.getProgram());
	shader.setMatrix(camera.getCombined());
	gSys->pSpriteRenderer->renderSprites();
	glUseProgram(0);
}

void CGameState::update(float dt)
{
	gameTime += dt;
	
	gSys->pClient->update();
	gSys->pPlayerController->sendInput();

	gSys->pPlayerController->updateMovement(dt);
	gSys->pEntitySystem->update();
	gSys->pConsole->update();

	enet_host_flush(gSys->pClient->client);
}

void CGameState::enter()
{

}

void CGameState::exit()
{

}
