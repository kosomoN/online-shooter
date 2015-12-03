#include "AnimationLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "GlobalSystem.h"

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
	std::string srows = content.substr(0, content.find(','));
	std::string scols = content.substr(content.find(',') + 1);

	int rows = atoi(srows.c_str());
	int cols = atoi(scols.c_str());;

	auto a = new CAnimation(rows,cols);
	m_anims.push_back(a);
	return a;
}
