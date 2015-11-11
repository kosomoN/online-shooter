#pragma once
#include "WindowSystem.h"
#include "EntitySystem.h"
#include "Input.h"
#include <string>
#include "SpriteBatch.h"
#include "StateSystem.h"
#include "SpriteRenderer.h"

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
	SpriteBatch* pSpriteBatch;
	StateSystem* pStateSystem;
	SpriteRenderer* pSpriteRenderer;

	void log(string);
private:

};

extern CGlobalSystem* gSys;
