#include "GlobalSystem.h"

CGlobalSystem::~CGlobalSystem()
{
	delete pWindowSystem;
}

void CGlobalSystem::init()
{
	pWindowSystem = new CWindowSystem;
	pWindowSystem->init(1280,720);
}

void CGlobalSystem::log(std::string text)
{
	printf(text.c_str());
}
