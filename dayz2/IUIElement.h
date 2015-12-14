#pragma once
#include "Sprite.h"
#include <Awesomium\WebCore.h>
#include <Awesomium/BitmapSurface.h>
#include <Awesomium/STLHelpers.h>
#include <string>
#include <glm\vec2.hpp>

struct IUIElement
{
	virtual ~IUIElement() {}
	virtual void init() = 0;
	virtual CSprite* getSprite() = 0;
	virtual Awesomium::WebView* getWebView() = 0;
	virtual glm::vec2& getScreenSpacePos() = 0;
};