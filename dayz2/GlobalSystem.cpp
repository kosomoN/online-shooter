#include "GlobalSystem.h"
#include "Console.h"
#include "TextureCache.h"


CGlobalSystem::~CGlobalSystem()
{
	delete pStateSystem;
	delete pSpriteBatch;
	delete pWindowSystem;
	delete pEntitySystem;
	delete pInput;
	delete pSpriteRenderer;
	delete pPlayerController;
	delete pClient;
	delete pConsole;
	delete pTextureCache;
	delete pGame;
}

void CGlobalSystem::init()
{
	pEntitySystem = new CEntitySystem;
	pInput = new CInput;
	pPlayerController = new CPlayerController;
	pWindowSystem = new CWindowSystem;
	pWindowSystem->init(1280, 720);
	pSpriteBatch = new CSpriteBatch(256);
	pStateSystem = new CStateSystem();
	pSpriteRenderer = new CSpriteRenderer;
	pClient = new CClient;
	pConsole = new CConsole;
	pTextureCache = new CTextureCache;
	pClient->init();
	pGame = new CGameState;
}

void CGlobalSystem::log(string text)
{
	printf(std::string(text+"\n").c_str());
}
