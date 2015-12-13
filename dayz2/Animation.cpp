#include "Animation.h"

#include "GlobalSystem.h"

CAnimation::CAnimation(int col, int row, float speed, glm::vec2 size, glm::vec2 rotPoint) :
m_frame(0.f),
m_loopLimit(-1),
m_loops(0),
isDone(true)
{
	calcUVs(col, row);
	m_speed = speed;
	float scale = 0.828f / 207.f;
	m_size = size * scale;
	m_rotPointOffset = rotPoint * scale;
}


CAnimation::~CAnimation()
{
}

glm::vec4& CAnimation::render()
{
	if (m_loops < m_loopLimit || m_loopLimit == -1)
	{
		m_uv = UVs[m_frame];

		m_frame += gSys->pGame->frameDelta * 30 * m_speed;

		if (floor(m_frame) >= UVs.size())
		{
			m_frame = 0.0f;
			m_loops++;
		}
		return m_uv;
	}

	isDone = true;

	return m_uv;
}

void CAnimation::setPlayLimit(int n)
{
	m_loopLimit = n;
	m_loops = 0;
	isDone = false;
}

void CAnimation::resetLoops()
{
	m_loops = 0;
	isDone = false;
}

void CAnimation::calcUVs(int cols, int rows)
{
	float u1 = 0, v1 = 0, u2 = 0, v2 = 0;
	float texWidth = (1.f / cols);
	float texHeight = (1.f / rows);
	for (int i = 0; i < rows; i++)
	{
		u1 = i*texHeight + texHeight;
		u2 = i*texHeight;
		for (int j = 0; j < cols; j++)
		{
			v2 = j*texWidth + texWidth;
			v1 = j*texWidth;
			UVs.push_back(glm::vec4(u1, v1, u2, v2));
		}
	}
}
