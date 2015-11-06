#pragma once

struct Vec2
{
	float x, y;
	Vec2(float px, float py) : x(px), y(y) {}
	Vec2(float xy = 0) : x(xy), y(xy) {}
	Vec2(const Vec2& v) { x = v.x; y = v.y; }
};