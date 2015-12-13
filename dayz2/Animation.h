#pragma once
#include <vector>
#include <glm\vec4.hpp>
#include <glm\vec2.hpp>

class CSprite;
class CAnimation
{
public:
	CAnimation(int,int,float,glm::vec2,glm::vec2 = glm::vec2(0.5));
	~CAnimation();

	glm::vec4& render();
	// Loops the animations n times
	void setPlayLimit(int n);
	void resetLoops();

	std::vector<glm::vec4> UVs;
	bool isDone;
	CSprite* m_pSprite;
	unsigned int m_textureId;
	glm::vec2 m_size;
	glm::vec2 m_rotPointOffset;
private:
	void calcUVs(int col, int row);
	float m_frame;
	float m_speed;
	int m_loops;
	int m_loopLimit;
	glm::vec4 m_uv = glm::vec4(0, 0, 0, 0);

};

