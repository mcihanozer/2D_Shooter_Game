#include "RigidBody.h"

RigidBody::RigidBody(const int id, const unsigned int color, const float width, const float height)
	:MovingObject(id, color, width, height)
{
	init();
}

RigidBody::RigidBody(const int id, const unsigned int color, const float width, const float height,
					 const float centX, const float centY)
	:MovingObject(id, color, width, height, centX, centY)
{
	init();
}

RigidBody::RigidBody(const int id, const unsigned int color, const float width, const float height,
	const float centX, const float centY, const float moveDirX, const float movedirY, eRigidBodyType type)
	: MovingObject(id, color, width, height, centX, centY, moveDirX, movedirY)
{
	init();

	mRigidBodyType = type;
}

void RigidBody::init()
{
	mIsCollided = false;
	mIsAlive = true;
	mCanRevive = true;
}

const eRigidBodyType RigidBody::getBodyType() const
{
	return mRigidBodyType;
}

const bool RigidBody::isCollided() const
{
	return mIsCollided;
}

void RigidBody::setCollided()
{
	mIsCollided = true;
}

void RigidBody::revertCollided()
{
	mIsCollided = false;
}

const bool RigidBody::isAlive() const
{
	return mIsAlive;
}

void RigidBody::revive()
{
	mIsRender = true;

	init();

	setVertices();
}

void RigidBody::setDead()
{
	mIsAlive = false;
}

const bool RigidBody::canRevive() const
{
	return mCanRevive;
}

void RigidBody::setCantRevive()
{
	mCanRevive = false;
}