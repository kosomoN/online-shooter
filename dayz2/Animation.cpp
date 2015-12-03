#include "Animation.h"



CAnimation::CAnimation(int col, int row):
frame(0.f)
{
	calcUVs(col, row);
}


CAnimation::~CAnimation()
{
}

glm::vec4& CAnimation::render()
{
	auto uv = UVs[frame];

	if (floor(frame += 0.1f) == UVs.size())
		frame = 0.0f;

	return *uv;
}

void CAnimation::calcUVs(int cols, int rows)
{
	float u1 = 0, v1 = 0, u2 = 0, v2 = 0;
	float texWidth = (1.f / cols);
	float texHeight = (1.f / rows);
	for (int i = 0; i < rows; i++)
	{
		u2 = i*texHeight + texHeight;
		u1 = i*texHeight;
		for (int j = 0; j < cols; j++)
		{
			v2 = j*texWidth + texWidth;
			v1 = j*texWidth;
			UVs.push_back(new glm::vec4(u1, v1, u2, v2));
		}
	}
}
