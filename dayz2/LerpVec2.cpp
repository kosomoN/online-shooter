#include "LerpVec2.h"

void LerpVec2::addValue(float x, float y, double time)
{
	if (values[0].time != -1)
	{
		//Discard if too old
		if (values[0].time > time)
			return;

		values[2] = values[1];
		values[1] = values[0];

		values[0].time = time;
		values[0].vec.x = x;
		values[0].vec.y = y;
	}
	else
	{
		if (values[0].time > time)
			return;

		//First time, populate whole buffer
		values[0].time = time;
		values[0].vec.x = x;
		values[0].vec.y = y;

		values[1] = values[0];
		values[2] = values[0];
	}
}

void LerpVec2::addValue(glm::vec2 vec, double time)
{
	addValue(vec.x, vec.y, time);
}

glm::vec2 LerpVec2::getLerp(double time)
{
	if (time >= values[0].time)
		return values[0].vec;
	
	if (time > values[1].time)
	{
		float t = (time - values[1].time) / (values[0].time - values[1].time);
		return values[1].vec + (values[0].vec - values[1].vec) * t;
	}
	
	if (time > values[2].time)
	{
		float t = (time - values[2].time) / (values[1].time - values[2].time);
		return values[2].vec + (values[1].vec - values[2].vec) * t;
	}

	return values[2].vec;
}
