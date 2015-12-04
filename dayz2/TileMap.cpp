#include "TileMap.h"

#include <iostream>
#include <rapidjson/filereadstream.h>
#include "GlobalSystem.h"
#include "Camera.h"
#include "TextureCache.h"

CTileMap::CTileMap(std::string jsonPath)
{
	FILE* pFile = fopen(jsonPath.c_str(), "r");
	if (!pFile)
	{
		gSys->log("Could not open map file: " + jsonPath);
		exit(1);
	}
	
	char buffer[65536];
	rapidjson::FileReadStream fileStream(pFile, buffer, sizeof(buffer));
	document.ParseStream(fileStream);

	if (document.HasParseError())
	{
		gSys->log("Error parsing map: " + jsonPath);
		exit(1);
	}

	if (!document["width"].IsInt())
	{
		gSys->log("Error parsing map width: " + jsonPath);
		exit(1);
	}

	m_width = document["width"].GetInt();

	if (!document["height"].IsInt())
	{
		gSys->log("Error parsing map tileheight: " + jsonPath);
		exit(1);
	}

	m_height = document["height"].GetInt();



	if (!document["tilewidth"].IsInt())
	{
		gSys->log("Error parsing map tilewidth: " + jsonPath);
		exit(1);
	}

	m_tileWidth = document["tilewidth"].GetInt();

	if (!document["tileheight"].IsInt())
	{
		gSys->log("Error parsing map tileheight: " + jsonPath);
		exit(1);
	}
	m_tileHeight = document["tileheight"].GetInt();

	m_layers.push_back(MapLayer());
	m_textureID = gSys->pTextureCache->getTexture("data/maps/mountain_landscape.png");	

	glBindTexture(GL_TEXTURE_2D, m_textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);
}

CTileMap::~CTileMap()
{
}

void CTileMap::renderMap()
{
	const glm::vec3& camPos = gSys->pGame->camera.getPosition();
	const glm::vec2& camSize = gSys->pGame->camera.getSize();

	glm::ivec2 bottomLeft(camPos.x - camSize.x / 2, camPos.y - camSize.y / 2);
	bottomLeft /= m_tileWidth;

	glm::ivec2 topRight(camPos.x + camSize.x / 2, camPos.y + camSize.y / 2);
	topRight /= m_tileHeight;
	topRight += 1;

	bottomLeft.x = max(min(bottomLeft.x, m_width), 0);
	bottomLeft.y = max(min(bottomLeft.y, m_height), 0);

	topRight.x = max(min(topRight.x, m_width), 0);
	topRight.y = max(min(topRight.y, m_height), 0);

	gSys->pSpriteBatch->begin(m_textureID);

	for (MapLayer layer : m_layers)
	{
		if (!layer.m_visible)
			continue;

		for (int x = bottomLeft.x; x < topRight.x; x++)
		{
			for (int y = bottomLeft.y; y < topRight.y; y++)
			{
				gSys->pSpriteBatch->drawVertices(x * m_tileWidth, y * m_tileHeight, (x + 1) * m_tileWidth, (y + 1) * m_tileHeight, 1 - 0.0625f, 0, 1, 0.0625f);
			}
		}
	}

	gSys->pSpriteBatch->end();
}
