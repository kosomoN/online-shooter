#pragma once
#include "IState.h"
#include "SpriteRenderer.h"
#include "Shader.h"
#include <string>
#include "Camera.h"

class CGameState : public IState
{
public:
	~CGameState();
	
	void init();
	void render();
	void update(float dt);
	void enter();
	void exit();

private:
	CShader shader = CShader("data/basic.glsl");
	CCamera camera = CCamera(1280, 720);
};

