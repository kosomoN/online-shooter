#pragma once
#include "WindowSystem.h"
#include "EntitySystem.h"
#include "Input.h"
#include <string>
#include "SpriteBatch.h"
#include "StateSystem.h"
#include "SpriteRenderer.h"
#include "PlayerController.h"
#include "Client.h"
#include <cstdint>

typedef std::string string;
typedef unsigned int uint;

class CGlobalSystem
{
public:
	CGlobalSystem() {};
	~CGlobalSystem();
	void init();

	CWindowSystem* pWindowSystem;
	CEntitySystem* pEntitySystem;
	CInput* pInput;
	CSpriteBatch* pSpriteBatch;
	CStateSystem* pStateSystem;
	CSpriteRenderer* pSpriteRenderer;
	CPlayerController* pPlayerController;
	CClient* pClient;

	void log(string);
private:

};

extern CGlobalSystem* gSys;
