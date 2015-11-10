#include "GameState.h"

#include "GlobalSystem.h"
#include "lodepng.h"
#include <vector>

GameState::~GameState()
{
	delete sprite;
}

void GameState::init()
{
	//Just testing, don't judge
	sprite = new Sprite(128, 128, 0, 0, 1, 1, 0);
	m_spriteRenderer.registerSprite(sprite);

	camera.setPosition(glm::vec2(540, 0));
}

void GameState::render()
{
	glUseProgram(shader.getProgram());
	shader.setMatrix(camera.getCombined());
	m_spriteRenderer.renderSprites();
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
