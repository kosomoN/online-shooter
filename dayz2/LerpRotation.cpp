#include "LerpRotation.h"

#include "GlobalSystem.h"
#include <glm/gtc/constants.hpp>

static const float PI = glm::pi<float>();

void LerpRotation::addValue(float value, double time)
{
	value = fmod(value, glm::pi<float>() * 2);
	if (value < 0)
		value += PI * 2;

	if (values[0].time != -1)
	{
		//Discard if too old
		if (values[0].time > time)
			return;

		values[2] = values[1];
		values[1] = values[0];

		values[0].time = time;
		values[0].value = value;
	}
	else
	{
		if (values[0].time > time)
			return;

		//First time, populate whole buffer
		values[0].time = time;
		values[0].value = value;

		values[1] = values[0];
		values[2] = values[0];
	}
}

float LerpRotation::getLerp(double time)
{
	if (time >= values[0].time)
		return values[0].value;

	if (time > values[1].time)
	{
		float t = (time - values[1].time) / (values[0].time - values[1].time);
		return values[1].value + (fmod(fmod(values[0].value - values[1].value, PI * 2) + PI * 3, PI * 2) - PI) * t;
	}

	if (time > values[2].time)
	{
		float t = (time - values[2].time) / (values[1].time - values[2].time);
		return values[2].value + (fmod(fmod(values[1].value - values[2].value, PI * 2) + PI * 3, PI * 2) - PI) * t;
	}

	return values[2].value;
}
