#pragma once
#include "WindowSystem.h"
#include <string>

class CGlobalSystem
{
public:
	CGlobalSystem() {};
	~CGlobalSystem();
	void init();
	CWindowSystem* pWindowSystem;
	void log(std::string);
private:

};

extern CGlobalSystem* gSys;