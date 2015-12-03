#include "TextureCache.h"
#include "lodepng.h"
#include "GlobalSystem.h"

CTextureCache::CTextureCache()
{
}

CTextureCache::~CTextureCache()
{
}

unsigned int CTextureCache::createTexture(std::string file)
{
	GLuint texture;

	unsigned int width, height;
	std::vector<unsigned char> image;

	auto e = lodepng::decode(image, width, height, file.c_str());

	if (e != 0)
	{
		gSys->log("Could not load texture: " + file);
		exit(1);
	}

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	m_texures[file] = texture;

	return texture;
}

unsigned int CTextureCache::getTexture(string file)
{
	if (m_texures.find(file) == m_texures.end())
		return createTexture(file);

	return m_texures[file];
}
