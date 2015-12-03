#pragma once

#include <string>
#include <vector>
#include <rapidjson/document.h>
#include <gl/glew.h>

class CTileMap
{
public:
	CTileMap(std::string jsonPath);
	~CTileMap();

	void renderMap();

private:
	rapidjson::Document document;

	struct MapLayer
	{
		std::string m_layerName;
		bool m_visible = true;
		std::vector<std::vector<uint8_t>> m_tileData;
	};
	std::vector<MapLayer> m_layers;
	uint16_t m_width, m_height;
	uint16_t m_tileWidth, m_tileHeight;
	GLuint m_textureID;
};

