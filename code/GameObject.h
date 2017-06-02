#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Geometry.h"

#include <vector>

// MCO: Abstract GameObject class. The base for anything that will be rendered.
class GameObject
{
public:

	GameObject() {}
	GameObject(const int id, const unsigned int color, const float width, const float height);
	GameObject(const int id, const unsigned int color, const float width, const float height,
			   const float centX, const float centY);

	~GameObject();

	virtual void displaySelf() = 0;
	virtual void setVertices() = 0;

	virtual void setWidth(const float& width);
	virtual void setHeight(const float& height);
	virtual const float getWidth() const;
	virtual const float getHeight() const;


	virtual const int getId() const;

	virtual void setPosition(const Vec2& pos);
	virtual void setPosition(const float& centX, const float& centY);
	virtual void setCenterRandomly();
	virtual Vec2 getCenter();


protected:

	bool mIsRender;

	unsigned int mColor;

	int mId;

	float mWidth;
	float mHeight;

	Vec2 mCenter;

	std::vector<Vec2> mVertices;
	
};

#endif
