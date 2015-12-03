#pragma once
#include <string>
#include <glm\vec4.hpp>
#include <vector>
#include "Animation.h"

class CAnimationLoader
{
public:
	CAnimationLoader();
	~CAnimationLoader();

	CAnimation* loadAnimation(std::string file);

private:
	std::vector<CAnimation*> m_anims;

};
