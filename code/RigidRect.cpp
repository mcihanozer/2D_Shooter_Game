#include "RigidRect.h"

#include "graphics.h"

#define SPEED 4 // RigidRect has a default speed

RigidRect::RigidRect()
{
	mId = -1;
	mIsRender = true;
	mIsAlive = true;
	mCanRevive = true;
	mIsCollided = false;
	mRigidBodyType = eRigidBodyType::eBox;

	mWidth = 100;
	mHeight = 100;
	mSpeed = SPEED;

	mColor = GetRGB(255, 0, 0);

	setCenterRandomly();

	getRandomDirection(mMoveDirection);

	setVertices();
}

RigidRect::RigidRect(const int id, const float width, const float height, unsigned int red, unsigned int green, unsigned int blue)
	:RigidBody(id, GetRGB(red, green, blue), width, height)
{
	mRigidBodyType = eRigidBodyType::eBox;

	mSpeed = SPEED;

	setCenterRandomly();

	getRandomDirection(mMoveDirection);

	setVertices();
}

RigidRect::RigidRect(const int id, const float width, const float height, const float centX, const float centY,
	unsigned int red, unsigned int green, unsigned int blue)
	:RigidBody(id, GetRGB(red, green, blue), width, height, centX, centY)
{
	mRigidBodyType = eRigidBodyType::eBox;

	mSpeed = SPEED;

	getRandomDirection(mMoveDirection);

	setVertices();

}

RigidRect::RigidRect(const int id, const float width, const float height, const float centX, const float centY,
	const float moveDirX, const float movedirY, unsigned int red, unsigned int green, unsigned int blue)
	:RigidBody(id, GetRGB(red, green, blue), width, height, centX, centY, moveDirX, movedirY, eRigidBodyType::eBox)
{
	mSpeed = SPEED;

	setVertices();
}

RigidRect::RigidRect(const int id, const unsigned int color, const float width, const float height)
	:RigidBody(id, color, width, height)
{
	setCenterRandomly();

	getRandomDirection(mMoveDirection);

	setVertices();
}

RigidRect::RigidRect(const int id, const unsigned int color, const float width, const float height,
	const float centX, const float centY)
	: RigidBody(id, color, width, height, centX, centY)
{
	getRandomDirection(mMoveDirection);

	setVertices();
}

RigidRect::RigidRect(const int id, const unsigned int color, const float width, const float height,
	const float centX, const float centY, const float moveDirX, const float movedirY, const eRigidBodyType type)
	: RigidBody(id, color, width, height, centX, centY, moveDirX, movedirY, type)
{
	setVertices();
}

void RigidRect::setVertices()
{
	mVertices.clear();

	mVertices.push_back(Vec2(mCenter.x - (mWidth * 0.5), mCenter.y - (mHeight * 0.5)));
	mVertices.push_back(Vec2(mCenter.x + (mWidth * 0.5), mCenter.y - (mHeight * 0.5)));
	mVertices.push_back(Vec2(mCenter.x - (mWidth * 0.5), mCenter.y + (mHeight * 0.5)));
	mVertices.push_back(Vec2(mCenter.x + (mWidth * 0.5), mCenter.y + (mHeight * 0.5)));
}

void RigidRect::displaySelf()
{
	if (mIsRender)
	{
		displayRect();
	}
}

void RigidRect::displayRect()
{
	// TODO Introduce face, vertex, etc. info
	DrawLine(mVertices[0].x, mVertices[0].y, mVertices[1].x, mVertices[1].y, mColor);
	DrawLine(mVertices[1].x, mVertices[1].y, mVertices[3].x, mVertices[3].y, mColor);
	DrawLine(mVertices[3].x, mVertices[3].y, mVertices[2].x, mVertices[2].y, mColor);
	DrawLine(mVertices[2].x, mVertices[2].y, mVertices[0].x, mVertices[0].y, mColor);
}

bool RigidRect::checkBorderCollision()
{
	// DO SOMETHING

	return false;
}

void RigidRect::move()
{
	checkBorderCollision();

	for (std::vector<Vec2>::iterator it = mVertices.begin(); it != mVertices.end(); it++)
	{
		it->x += (mMoveDirection.x * mSpeed);
		it->y += (mMoveDirection.y * mSpeed);
	}

	mCenter.x += (mMoveDirection.x * mSpeed);
	mCenter.y += (mMoveDirection.y * mSpeed);
}

bool RigidRect::checkCollision(const RigidBody* obj) const
{
	// Axis-aligned 2D bounding box (Bbox) collision detection
	// ASSUMPTION: Since the rigid bodies are only Clock and Bullet, which are basicly
	//				Bboxes, basic "rectangle collision detection" is enough for this project
	// WARNING: This code may cause overlapping } Best solution to prevent overlapping:
	//          Introduce phsycis based collision handling (Requires more CPU cycle).
	//			Easy solution: Keep last position, if they collide move them back to previous position
	if (getBBoxUp().x < (obj->getBBoxUp().x + obj->getWidth()) &&
		(getBBoxUp().x + mWidth)> obj->getBBoxUp().x &&
		getBBoxUp().y < (obj->getBBoxUp().y + obj->getHeight()) &&
		(getBBoxUp().y + mHeight) > obj->getBBoxUp().y
		)
	{
		return true;
	}

	return false;
}

void RigidRect::collide(const eRigidBodyType type)
{
	// DO SOMETHING!
}

const Vec2&  RigidRect::getBBoxUp() const
{
	return mVertices[0];
}

const Vec2& RigidRect::getBBoxDown() const
{
	return mVertices[3];
}