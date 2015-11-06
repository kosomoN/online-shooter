#include "GlobalSystem.h"

CGlobalSystem::~CGlobalSystem()
{
	delete pWindowSystem;
	delete pEntitySystem;
}

void CGlobalSystem::init()
{
	pEntitySystem = new CEntitySystem;

	pWindowSystem = new CWindowSystem;
	pWindowSystem->init(1280, 720);
}

void CGlobalSystem::log(string text)
{
	printf(std::string(text+"\n").c_str());
}
