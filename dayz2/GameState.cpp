#include "GameState.h"

#include "GlobalSystem.h"
#include "lodepng.h"
#include <vector>

GameState::~GameState()
{
}

void GameState::init()
{
	Sprite* sprite = gSys->pSpriteRenderer->addSprite(128, 128, 0, 0, 1, 1, 0);
	camera.setPosition(glm::vec2(540, 0));
}

void GameState::render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shader.getProgram());
	shader.setMatrix(camera.getCombined());
	gSys->pSpriteRenderer->renderSprites();
	glUseProgram(0);

}

void GameState::update(float dt)
{

}

void GameState::enter()
{

}

void GameState::exit()
{

}
