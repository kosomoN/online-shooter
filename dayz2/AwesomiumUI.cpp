#include "AwesomiumUI.h"
#include "GlobalSystem.h"
#include <Awesomium/WebCore.h>
#include <Awesomium/BitmapSurface.h>
#include <Awesomium/STLHelpers.h>
#include <string>
#include <GL\glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Sprite.h"
#include "Player.h"

using namespace Awesomium;

CAwesomiumUI::CAwesomiumUI()
{
}


CAwesomiumUI::~CAwesomiumUI()
{
}

CSprite* CAwesomiumUI::createUiObject(int width, int height, int x, int y, std::string htmlFile)
{
	std::ifstream f;
	f.open(htmlFile.c_str());

	if (!f.is_open())
	{
		gSys->log("Cannot open html file: " + htmlFile);
		exit(1);
	}

	std::stringstream ss;
	ss << f.rdbuf();
	std::string content = ss.str();

	auto web_core = WebCore::Initialize(WebConfig());
	auto view = web_core->CreateWebView(1280,720);
	view->SetTransparent(true);
	WebURL url(WSLit(std::string("data:text/html,"+content).c_str()));
	view->LoadURL(url);
	auto BindMethods(view);

	while (view->IsLoading())
		web_core->Update();
	Sleep(300);
	web_core->Update();

	auto surface = (BitmapSurface*)view->surface();

	int w = surface->width();
	int h = surface->height();

	unsigned char *buffer = new unsigned char[w * h * 4];
	surface->CopyTo(buffer, w * 4, 4, false, false);

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, buffer);

	delete[] buffer;

	float scale = 0.828f / 207.f;
	auto sprite = gSys->pSpriteRenderer->addSprite(width * scale, height * scale, 0, 1, 1, 0, "");
	sprite->m_texture = texture;
	sprite->m_pos = glm::vec2(x, y) * scale;
	m_uiSprites.push_back(sprite);
	return sprite;
}

void CAwesomiumUI::update()
{
	if (CPlayer* pPlayer = gSys->pPlayer)
	{
		for (CSprite* s : m_uiSprites)
		{
			glm::vec2 relativePos = pPlayer->m_pos.getLerp(gSys->pGame->gameTime - 0.1) - (gSys->pGame->camera.getSize() / 2.f);
			s->m_pos = relativePos;
		}
	}
}
