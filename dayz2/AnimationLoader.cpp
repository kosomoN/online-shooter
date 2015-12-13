#include "AnimationLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "GlobalSystem.h"
#include "Utils.hpp"

CAnimationLoader::CAnimationLoader()
{
}

CAnimationLoader::~CAnimationLoader()
{
	for (CAnimation* a : m_anims)
		delete a;
}

CAnimation* CAnimationLoader::loadAnimation(std::string ifile)
{
	std::vector<glm::vec4> uvs;
	std::ifstream f;
	f.open(ifile.c_str());
	
	if (!f.is_open())
	{
		gSys->log("Cannot open anim file: " + ifile);
		exit(1);
	}

	std::stringstream ss;
	ss << f.rdbuf();
	std::string content = ss.str();
	auto props = Split(content, ',');

	int rows = atoi(props[0].c_str());
	int cols = atoi(props[1].c_str());
	float speed = atof(props[2].c_str());
	glm::vec2 size = glm::vec2(atof(props[3].c_str()), atof(props[4].c_str()));
	glm::vec2 rotPoint = glm::vec2(atof(props[5].c_str()), atof(props[6].c_str()));

	auto a = new CAnimation(rows,cols,speed,size,rotPoint);
	m_anims.push_back(a);
	return a;
}
