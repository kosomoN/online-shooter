#include "GameState.h"

#include "GlobalSystem.h"
#include "lodepng.h"
#include <vector>
#include "Player.h"

CGameState::~CGameState()
{
}

std::vector<CSprite*>sprites;


void CGameState::init()
{
	new CPlayer(0);
	camera.setPosition(glm::vec2(540, 0));
}

void CGameState::render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shader.getProgram());
	shader.setMatrix(camera.getCombined());
	gSys->pSpriteRenderer->renderSprites();
	for(auto s : sprites)
		s->m_rotation += 0.01;
	glUseProgram(0);
}

void CGameState::update(float dt)
{
	gSys->pClient->update();
}

void CGameState::enter()
{

}

void CGameState::exit()
{

}
