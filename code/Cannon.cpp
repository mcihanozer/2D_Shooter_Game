#include "Cannon.h"

#include <math.h>

#include "graphics.h"

#define SPEED 4 // MCO: Value of updating the rotation angle (mTheta)

Cannon::Cannon(const int id, const float width, const float height, const float centX, const float centY,
	unsigned int red, unsigned int green, unsigned int blue)
	: MovingObject(id, GetRGB(red, green, blue), width, height, centX, centY)
{
	mTheta = 0;

	setVertices();

	mMoveDirection.x = mCenter.x - mPivot.x;
	mMoveDirection.y = mCenter.y - mPivot.y;
}

Cannon::~Cannon()
{
	mTransformedVertices.clear();
}

void Cannon::displaySelf()
{
	if (mIsRender)
	{
		// TODO Introduce face, vertex, etc. info
		DrawLine(mTransformedVertices[0].x, mTransformedVertices[0].y, mTransformedVertices[1].x, mTransformedVertices[1].y, mColor);
		DrawLine(mTransformedVertices[0].x, mTransformedVertices[0].y, mTransformedVertices[2].x, mTransformedVertices[2].y, mColor);
		DrawLine(mTransformedVertices[1].x, mTransformedVertices[1].y, mTransformedVertices[2].x, mTransformedVertices[2].y, mColor);
	}
}

void Cannon::setVertices()
{
	mVertices.clear();
	mTransformedVertices.clear();

	mVertices.push_back(Vec2(mCenter.x, mCenter.y));
	mVertices.push_back(Vec2(mCenter.x - mWidth * 0.5, mCenter.y + mHeight));
	mVertices.push_back(Vec2(mCenter.x + mWidth * 0.5, mCenter.y + mHeight));

	mTransformedVertices.push_back(Vec2(mCenter.x, mCenter.y));
	mTransformedVertices.push_back(Vec2(mCenter.x - mWidth * 0.5, mCenter.y + mHeight));
	mTransformedVertices.push_back(Vec2(mCenter.x + mWidth * 0.5, mCenter.y + mHeight));

	mPivot.x = mCenter.x;
	mPivot.y = mCenter.y + mHeight;
}

void Cannon::turn(const eDirection dir)
{
	if (dir == eDirection::eLeft)
	{
		mTheta = max(-90, mTheta - SPEED);
		rotate();
	}

	if (dir == eDirection::eRight)
	{
		mTheta = min(90, mTheta + SPEED);
		rotate();
	}
}

void Cannon::rotate()
{
	// Rotation of a point about an arbitrary point (Pivot point)
	float angle = toRadian(mTheta);

	// Rotate all vertices from rest pose location
	for (int vi = 0; vi < mVertices.size(); vi++)
	{
		mTransformedVertices[vi].x = cos(angle) * (mVertices[vi].x - mPivot.x) - sin(angle) * (mVertices[vi].y - mPivot.y) + mPivot.x;
		mTransformedVertices[vi].y = sin(angle) * (mVertices[vi].x - mPivot.x) + cos(angle) * (mVertices[vi].y - mPivot.y) + mPivot.y;
	}
}

Vec2 Cannon::getTransformedCenter()
{
	return mTransformedVertices[0];
}
Vec2 Cannon::getLookDirection()
{
	Vec2 lookDir;

	lookDir.x = mTransformedVertices[0].x - mPivot.x;
	lookDir.y = mTransformedVertices[0].y - mPivot.y;

	return lookDir;
}