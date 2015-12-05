#pragma once

struct LerpRotation
{
public:
	void addValue(float value, double time);
	float getLerp(double time);
private:

	struct LerpValue
	{
		float value;
		double time = -1;
	};

	LerpValue values[3];

};