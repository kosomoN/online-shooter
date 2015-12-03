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
	camera.setPosition(gSys->pPlayer->m_pos.getLerp(gSys->pGame->gameTime));
	shader.setMatrix(camera.getCombined());
	map.renderMap();
	gSys->pSpriteRenderer->renderSprites();
	glUseProgram(0);
}

void CGameState::update()
{
	gameTime = glfwGetTime() + serverTimeDelta;
	
	gSys->pClient->update();
	gSys->pPlayerController->sendInput();

	gSys->pPlayerController->updateMovement();
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
