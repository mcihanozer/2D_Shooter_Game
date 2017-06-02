#ifndef GEOMETRY_H
#define GEOMETRY_H

// TODO Add mathematical expressions (operators) by overloading
struct Vec2
{
	Vec2()
	{
		x = 0;
		y = 0;
	}
	Vec2(const float _x, const float _y)
		: x(_x), y(_y)
	{}

	float x, y;
};

#endif // !GEOMETRY_H
