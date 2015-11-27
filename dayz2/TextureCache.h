#pragma once
#include <unordered_map>
#include <string>
#include <glm\vec2.hpp>

class CTextureCache
{
public:
	CTextureCache();
	~CTextureCache();

	unsigned int getTexture(std::string file);

private:
	unsigned int createTexture(std::string file);
	std::unordered_map<std::string, unsigned int> m_texures;

};
