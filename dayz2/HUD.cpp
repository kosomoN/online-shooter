#include "AwesomiumUI.h"
#include "GlobalSystem.h"
#include "TextureCache.h"
#include "HUD.h"
#include <GL\glew.h>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace Awesomium;

CHUD::CHUD(int width, int height, int x, int y, std::string html)
{
	m_width = width;
	m_height = height;
	m_x = x;
	m_y = y;
	m_html = html;
	gSys->pAwesomiumUI->registerUIElement(this);
}

CHUD::~CHUD()
{
}

void CHUD::init()
{
	std::ifstream f;
	f.open(m_html.c_str());

	if (!f.is_open())
	{
		gSys->log("Cannot open html file: " + m_html);
		exit(1);
	}

	std::stringstream ss;
	ss << f.rdbuf();
	std::string content = ss.str();

	auto web_core = WebCore::Initialize(WebConfig());
	auto view = web_core->CreateWebView(m_width * 1.5, m_height * 1.5);
	m_pWebView = view;
	view->SetTransparent(true);
	WebURL url(WSLit(std::string("data:text/html,"+content).c_str()));
	view->LoadURL(url);
	auto BindMethods(view);

	// Wait for the page and the scripts to load before we proceed.
	while (view->IsLoading())
		web_core->Update();
	Sleep(300);
	web_core->Update();

	auto texture = gSys->pTextureCache->createUITexture((BitmapSurface*)view->surface());

	// Create sprite
	float scale = gSys->pGame->camera.getSize().y / (float)m_height;
	CSprite* sprite = gSys->pSpriteRenderer->addSprite(m_width*scale, m_height*scale, 0, 1, 1, 0, "data/survivor.png");
	sprite->m_texture = texture;
	sprite->m_pos = glm::vec2(0, 0);
	m_x *= scale;
	m_y *= scale;
	m_pSprite = sprite;
}

void CHUD::update(int health, int ammo)
{
	JSValue win = m_pWebView->ExecuteJavascriptWithResult(WSLit("window"), WSLit(""));

	if (win.IsObject())
	{
		JSArray args;
		args.Push(WSLit(std::to_string(health).c_str()));
		win.ToObject().Invoke(WSLit("setStats"), args);
	}

	glDeleteTextures(1, &m_pSprite->m_texture);	
	auto texture = gSys->pTextureCache->createUITexture((BitmapSurface*)m_pWebView->surface());
	m_pSprite->m_texture = texture;
}


