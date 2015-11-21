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
	~CGameState();
	
	void init();
	void render();
	void update(float dt);
	void enter();
	void exit();
	CPlayer* getClientPlayer() { return m_pClientPlayer; }

private:
	CShader shader = CShader("data/basic.glsl");
	CCamera camera = CCamera(1280, 720);
	CPlayer* m_pClientPlayer;
};

