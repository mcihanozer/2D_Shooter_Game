#ifndef CLOCK_H
#define CLOCK_H

#include "Common.h"

#include "RigidRect.h"

// Clock class: "enemy" class. Generated by GameManager, interacts with Bullet
class Clock : public RigidRect
{
public:
	Clock();

	Clock(const int id, const float width, const float height, unsigned int red = 255, unsigned int green = 0, unsigned int blue = 0);

	Clock(const int id, const float width, const float height, const float centX, const float centY,
		 unsigned int red = 255, unsigned int green = 0, unsigned int blue = 0);

	Clock(const int id, const float width, const float height, const float centX, const float centY,
		const float moveDirX, const float movedirY, unsigned int red = 255, unsigned int green = 0, unsigned int blue = 0);

	void displaySelf();
	void collide(const eRigidBodyType type);

private:

	void setSpeed();
	bool checkBorderCollision();
	bool bounce();
	bool getShot();

};

#endif // !CLOCK_H
