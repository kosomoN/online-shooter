#include "GlobalSystem.h"

CGlobalSystem::~CGlobalSystem()
{
	delete pStateSystem;
	delete pSpriteBatch;
	delete pWindowSystem;
	delete pEntitySystem;
	delete pInput;
}

void CGlobalSystem::init()
{
	pEntitySystem = new CEntitySystem;
	pInput = new CInput;
	pWindowSystem = new CWindowSystem;
	pWindowSystem->init(1280, 720);
	pSpriteBatch = new SpriteBatch(256);
	pStateSystem = new StateSystem();
}

void CGlobalSystem::log(string text)
{
	printf(std::string(text+"\n").c_str());
}
