#pragma once
#include "WindowSystem.h"
#include "EntitySystem.h"
#include <string>
typedef std::string string;
class CGlobalSystem
{
public:
	CGlobalSystem() {};
	~CGlobalSystem();
	void init();

	CWindowSystem* pWindowSystem;
	CEntitySystem* pEntitySystem;

	void log(string);
private:

};

extern CGlobalSystem* gSys;
