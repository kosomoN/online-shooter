#pragma once
#include "WindowSystem.h"
#include "EntitySystem.h"
#include "Input.h"
#include <string>

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

	void log(string);
private:

};

extern CGlobalSystem* gSys;
