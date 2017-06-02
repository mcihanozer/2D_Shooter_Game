#include "Bullet.h"

#include "graphics.h"

#define SPEED  0.5// Default speed for bullet

Bullet::Bullet(const int id, const float width, const float height, const float centX, const float centY,
				const float moveDirX, const float movedirY, unsigned int red, unsigned int green, unsigned int blue)
	:RigidRect(id, GetRGB(red, green, blue), width, height, centX, centY, moveDirX, movedirY, eRigidBodyType::eBullet)
{
	mSpeed = SPEED;
}

void Bullet::displaySelf()
{
	if (mIsRender)
	{
		displayRect();
	}
}

bool Bullet::checkBorderCollision()
{
	for (std::vector<Vec2>::iterator it = mVertices.begin(); it != mVertices.end(); it++)
	{
		if (it->x <= 0 || it->x >= SCREEN_WIDTH)
		{
			setDead();
			return true;
		}
		else if (it->y <= 0 || it->y >= SCREEN_HEIGHT)
		{
			setDead();
			return true;
		}
	}

	return false;
}

void Bullet::collide(const eRigidBodyType type)
{
	if (eRigidBodyType::eClock == type)
	{
		explode();
	}
}

void Bullet::explode()
{
	setDead();
}