#include "GlobalSystem.h"

CGlobalSystem::~CGlobalSystem()
{
	delete pStateSystem;
	delete pSpriteBatch;
	delete pWindowSystem;
	delete pEntitySystem;
	delete pInput;
	delete pSpriteRenderer;
}

void CGlobalSystem::init()
{
	pEntitySystem = new CEntitySystem;
	pInput = new CInput;
	pWindowSystem = new CWindowSystem;
	pWindowSystem->init(1280, 720);
	pSpriteBatch = new SpriteBatch(256);
	pStateSystem = new StateSystem();
	pSpriteRenderer = new SpriteRenderer;
}

void CGlobalSystem::log(string text)
{
	printf(std::string(text+"\n").c_str());
}
