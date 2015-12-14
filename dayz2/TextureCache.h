#pragma once
#include <unordered_map>
#include <string>
#include <glm\vec2.hpp>

namespace Awesomium
{
	class BitmapSurface;
}

class CTextureCache
{
public:
	CTextureCache();
	~CTextureCache();

	unsigned int getTexture(std::string file);
	unsigned int createUITexture(Awesomium::BitmapSurface* surface);

private:
	unsigned int createTexture(std::string file);
	std::unordered_map<std::string, unsigned int> m_texures;

};
