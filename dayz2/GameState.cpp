#include "AwesomiumUI.h"
#include "GameState.h"
#include "GlobalSystem.h"
#include "lodepng.h"
#include "Console.h"
#include "Zombie.h"
#include <vector>
#include "main.h"
#include "HUD.h"

CGameState::~CGameState()
{
}

void CGameState::init()
{
	pGameHud = new CHUD(1280, 720, 0, 0, "data/ui.html");
}

void CGameState::render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shader.getProgram());
	camera.setPosition(gSys->pPlayer->m_pos.getLerp(gSys->pGame->gameTime));
	shader.setMatrix(camera.getCombined());
	map.renderMap();
	gSys->pSpriteRenderer->renderSprites();
	gSys->pAwesomiumUI->update();
	glUseProgram(0);
}

void CGameState::update()
{
	gameTime = glfwGetTime() + serverTimeDelta;
	
	gSys->pClient->update();
	gSys->pPlayerController->sendInput();

	gSys->pb2World->Step(gSys->pGame->frameDelta, 6, 2);
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
