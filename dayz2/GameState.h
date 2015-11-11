#pragma once
#include "IState.h"
#include "SpriteRenderer.h"
#include "Shader.h"
#include <string>
#include "Camera.h"

class GameState : public IState
{
public:
	~GameState();
	
	void init();
	void render();
	void update(float dt);
	void enter();
	void exit();

private:
	Shader shader = Shader("data/basic.glsl");
	Camera camera = Camera(1280, 720);
};

