#pragma once
#include "IUIElement.h"

class CHUD : public IUIElement
{
public:
	CHUD(int,int,int,int,std::string);
	~CHUD();

	// IUIElement
	virtual void init();
	virtual CSprite* getSprite() { return m_pSprite; }
	virtual Awesomium::WebView* getWebView() { return m_pWebView; }
	virtual glm::vec2& getScreenSpacePos() { return glm::vec2(m_x, m_y); }
	// ~IUIElement
	void update(int health, int ammo);

private:
	Awesomium::WebView* m_pWebView;
	CSprite* m_pSprite;
	int m_width, m_height, m_x, m_y;
	std::string m_html;
};

