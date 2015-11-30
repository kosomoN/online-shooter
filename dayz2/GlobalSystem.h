#pragma once
#include "EntitySystem.h"
#include "Input.h"
#include <string>
#include "SpriteBatch.h"
#include "StateSystem.h"
#include "SpriteRenderer.h"
#include "PlayerController.h"
#include "Client.h"
#include <cstdint>
#include "WindowSystem.h"
#include "GameState.h"

class CConsole;
class CTextureCache;

typedef std::string string;

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
	CPlayer* pPlayer;
	CConsole* pConsole;
	CTextureCache* pTextureCache;
	CGameState* pGame;
	double lastTimeRequest = 0;

	void log(string);
private:

};

extern CGlobalSystem* gSys;