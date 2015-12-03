#pragma once
#include "IState.h"
#include "SpriteRenderer.h"
#include "Shader.h"
#include <string>
#include "Camera.h"
#include "Player.h"
#include "TileMap.h"

class CGameState : public IState
{
public:
	CGameState() {};
	~CGameState();
	
	void init();
	void render();
	void update();
	void enter();
	void exit();
	CShader shader = CShader("data/basic.glsl");
	double gameTime = 0, frameDelta = 0;
	double serverTimeDelta = 0;
	CCamera camera = CCamera(1280, 720);
	CTileMap map { "data/maps/Test.json" };
};

