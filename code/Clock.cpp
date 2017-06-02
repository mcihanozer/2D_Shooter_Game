#include "Clock.h"

#include "graphics.h"
#include "time.h"

#define BASE_SPEED 4	// Minimum speed for Clock
#define DEAD_SIZE  10	// Minimum size that clock may go down

// Line size for clock
#define HOUR_SIZE 0.3
#define MINUTE_SIZE 0.35
#define SECOND_SIZE 0.45

Clock::Clock()
	:RigidRect()
{
	mCanRevive = true;

	mRigidBodyType = eRigidBodyType::eClock;
	setSpeed();
}

Clock::Clock(const int id, const float width, const float height, unsigned int red, unsigned int green, unsigned int blue)
	:RigidRect(id, GetRGB(red, green, blue), width, height)
{
	mCanRevive = true;

	mRigidBodyType = eRigidBodyType::eClock;
	setSpeed();
}

Clock::Clock(const int id, const float width, const float height, const float centX, const float centY,
			unsigned int red, unsigned int green, unsigned int blue)
	:RigidRect(id, GetRGB(red, green, blue), width, height, centX, centY)
{
	mCanRevive = true;

	mRigidBodyType = eRigidBodyType::eClock;
	setSpeed();
}

Clock::Clock(const int id, const float width, const float height, const float centX, const float centY,
	const float moveDirX, const float movedirY, unsigned int red, unsigned int green, unsigned int blue)
	:RigidRect(id, GetRGB(red, green, blue), width, height, centX, centY, moveDirX, movedirY, eRigidBodyType::eClock)
{
	mCanRevive = true;

	setSpeed();
}

void Clock::setSpeed()
{
	mSpeed = ((float)rand() / (RAND_MAX)) + BASE_SPEED; // (rand() % (BASE_SPEED + 1)) + BASE_SPEED;
}

void Clock::displaySelf()
{
	if (mIsRender)
	{
		// TODO Introduce face, vertex, etc. info
		displayRect();

		// Draw the time
		int hour, minute, second;
		GetTime(hour, minute, second);

		// Set hour line
		// TODO endX and endY can be removed
		float endX = mCenter.x;
		float endY = mCenter.y - (mHeight * HOUR_SIZE);
		rotateAroundPivot(endX, endY, mCenter.x, mCenter.y, (30 * (hour %= 12)));
		DrawLine(mCenter.x, mCenter.y, endX, endY, GetRGB(255, 255, 0));

		// Set minute line
		endX = mCenter.x;
		endY = mCenter.y - (mHeight * MINUTE_SIZE);
		rotateAroundPivot(endX, endY, mCenter.x, mCenter.y, (6 * minute));
		DrawLine(mCenter.x, mCenter.y, endX, endY, GetRGB(255, 0, 255));

		// Set second line
		endX = mCenter.x;
		endY = mCenter.y - (mHeight * SECOND_SIZE);
		rotateAroundPivot(endX, endY, mCenter.x, mCenter.y, (6 * second));
		DrawLine(mCenter.x, mCenter.y, endX, endY, GetRGB(255, 255, 255));
	}
}

bool Clock::checkBorderCollision()
{
	for (std::vector<Vec2>::iterator it = mVertices.begin(); it != mVertices.end(); it++)
	{
		if (it->x <= 0 || it->x >= SCREEN_WIDTH)
		{
			mMoveDirection.x *= -1;
			return true;
		}
		
		if (it->y <= 0 || it->y >= SCREEN_HEIGHT)
		{
			mMoveDirection.y *= -1;
			return true;
		}
	}

	return false;

}

void Clock::collide(const eRigidBodyType type)
{
	if (eRigidBodyType::eClock == type)
	{
		bounce();
	}
	else if (eRigidBodyType::eBullet == type)
	{
		getShot();
	}
}

bool Clock::bounce()
{
	mMoveDirection.x *= -1;
	mMoveDirection.y *= -1;

	return true;
}

bool Clock::getShot()
{
	setDead();

	if (mWidth < DEAD_SIZE || mHeight < DEAD_SIZE)
	{
		mCanRevive = false;
	}

	return true;
}