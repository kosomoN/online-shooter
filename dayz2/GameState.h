#pragma once
#include "IState.h"
#include "SpriteRenderer.h"
#include "Shader.h"
#include <string>
#include "Camera.h"
#include "Player.h"

class CGameState : public IState
{
public:
	CGameState() {};
	~CGameState();
	
	void init();
	void render();
	void update(float dt);
	void enter();
	void exit();
	CPlayer* getClientPlayer() { return m_pClientPlayer; }
	CShader shader = CShader("data/basic.glsl");
	double gameTime = 0;
private:
	CCamera camera = CCamera(1280, 720);
	CPlayer* m_pClientPlayer;
};

