#include "GameObject.h"

#include "Common.h"

GameObject::GameObject(const int id, const unsigned int color, const float width, const float height)
	: mId(id), mColor(color), mWidth(width), mHeight(height)
{
	mIsRender = true;
}

GameObject::GameObject(const int id, const unsigned int color, const float width, const float height,
					   const float centX, const float centY)
	: mId(id), mColor(color), mWidth(width), mHeight(height)
{
	mIsRender = true;

	mCenter.x = centX;
	mCenter.y = centY;
}

GameObject::~GameObject()
{
	mVertices.clear();
}

void GameObject::setWidth(const float& width)
{
	mWidth = width;
}

void GameObject::setHeight(const float& height)
{
	mHeight = height;
}

const float GameObject::getWidth() const
{
	return mWidth;
}

const float GameObject::getHeight() const
{
	return mHeight;
}

const int GameObject::getId() const
{
	return mId;
}

void GameObject::setPosition(const Vec2& pos)
{
	mCenter.x = pos.x;
	mCenter.y = pos.y;
}

void GameObject::setPosition(const float& centX, const float& centY)
{
	mCenter.x = centX;
	mCenter.y = centY;
}

// Set position randomly in the screen borders
void GameObject::setCenterRandomly()
{
	// WARNING: This code may cause overlapping of the objects depending on the random value
	// Easy solution:
	// - Keep last position initiated
	// - Get a new position until it does not overlap
	mCenter.x = (rand() % (int)(SCREEN_WIDTH - (mWidth + 1))) + (mWidth * 0.5) + 1;
	mCenter.y = (rand() % (int)(SCREEN_HEIGHT - (mHeight + 1))) + (mHeight * 0.5) + 1;
}

Vec2 GameObject::getCenter()
{
	return mCenter;
}