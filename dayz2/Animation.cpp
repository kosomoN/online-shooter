#include "Animation.h"

#include "GlobalSystem.h"

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

	frame += gSys->pGame->frameDelta * 30;

	if (floor(frame) >= UVs.size())
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
		u1 = i*texHeight + texHeight;
		u2 = i*texHeight;
		for (int j = 0; j < cols; j++)
		{
			v2 = j*texWidth + texWidth;
			v1 = j*texWidth;
			UVs.push_back(new glm::vec4(u1, v1, u2, v2));
		}
	}
}
