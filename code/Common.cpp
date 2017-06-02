#include "Common.h"

#include <cstdlib>

int SCREEN_WIDTH;
int SCREEN_HEIGHT;

float toRadian(const float degree)
{
	return degree * PI / 180.0;
}

// Rotation of a point about an arbitrary point (Pivot point)
void rotateAroundPivot(float& rotX, float& rotY, const float pivotX, const float pivotY, const float theta)
{
	float angle = toRadian(theta);

	float restX = rotX;
	float restY = rotY;

	rotX = cos(angle) * (restX - pivotX) - sin(angle) * (restY - pivotY) + pivotX;
	rotY = sin(angle) * (restX - pivotX) + cos(angle) * (restY - pivotY) + pivotY;
}

Vec2 getRandomDirection()
{
	Vec2 dir;

	int direction = 1;
	if ((float)rand() / (RAND_MAX) < 0.5)
	{
		direction *= -1;
	}

	dir.x = direction *  ((float)rand() / (RAND_MAX));
	dir.y = direction *  ((float)rand() / (RAND_MAX));

	return dir;
}

void getRandomDirection(Vec2& dir)
{
	int direction = 1;
	if ((float)rand() / (RAND_MAX) < 0.5)
	{
		direction *= -1;
	}

	dir.x = direction *  ((float)rand() / (RAND_MAX));
	dir.y = direction *  ((float)rand() / (RAND_MAX));
}