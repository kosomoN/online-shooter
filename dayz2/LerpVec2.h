#pragma once

#include <glm/glm.hpp>


struct LerpVec2
{
public:
    
    void addValue(float x, float y, double time);
    void addValue(glm::vec2 vec, double time);
    glm::vec2 getLerp(double time);
private:

	struct LerpValue
	{
		glm::vec2 vec;
		double time = -1;
	};

    LerpValue values[3];

};