#pragma once
#include <vector>
#include <glm\vec4.hpp>

class CAnimation
{
public:
	CAnimation(int,int,float);
	~CAnimation();

	glm::vec4& render();

	std::vector<glm::vec4*> UVs;
	bool activated;
private:
	void calcUVs(int col, int row);
	float m_frame;
	float m_speed;

};

