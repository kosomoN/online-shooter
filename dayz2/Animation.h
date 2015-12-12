#pragma once
#include <vector>
#include <glm\vec4.hpp>

class CAnimation
{
public:
	CAnimation(int,int,float);
	~CAnimation();

	glm::vec4& render();
	// Loops the animations n times
	void setPlayLimit(int n);
	void resetLoops();

	std::vector<glm::vec4> UVs;
	bool isDone;
private:
	void calcUVs(int col, int row);
	float m_frame;
	float m_speed;
	int m_loops;
	int m_loopLimit;

};

