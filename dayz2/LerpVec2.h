#pragma once

#include <glm/glm.hpp>


class LerpVec2
{
public:
    
    void addValue(float x, float y, int time);
    glm::vec2 getLerp(int time);
private:
    glm::vec2 values[3];

	struct LerpValue
	{
		glm::vec2 vec;
		int time;
	};
};