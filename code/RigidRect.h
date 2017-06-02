#ifndef RIGIDRECT_H
#define RIGIDRECT_H

#include "RigidBody.h"

// RigidRect is a base class for any kind of moving and rigid-body rectangle (renderable) object.
// It also can be used as a 2D bounding box.
// Currently, RigidRect is a base class for Clock and Bullet objects.
class RigidRect : public RigidBody
{
public:

	RigidRect();

	RigidRect(const int id, const float width, const float height, unsigned int red = 255, unsigned int green = 0, unsigned int blue = 0);

	RigidRect(const int id, const float width, const float height, const float centX, const float centY,
		unsigned int red = 255, unsigned int green = 0, unsigned int blue = 0);

	RigidRect(const int id, const float width, const float height, const float centX, const float centY,
		const float moveDirX, const float movedirY, unsigned int red = 255, unsigned int green = 0, unsigned int blue = 0);

	// For Clock and Bullet inheritance

	RigidRect(const int id, const unsigned int color, const float width, const float height);

	RigidRect(const int id, const unsigned int color, const float width, const float height,
		const float centX, const float centY);

	RigidRect(const int id, const unsigned int color, const float width, const float height,
		const float centX, const float centY, const float moveDirX, const float movedirY, const eRigidBodyType type);

	void move();
	void setVertices();

	const Vec2& getBBoxUp() const;
	const Vec2& getBBoxDown() const;

	// May need to be overrided
	void displaySelf();

	// May need to be overrided
	bool checkCollision(const RigidBody* obj) const;

	// May need to be overrided
	void collide(const eRigidBodyType type);

protected:

	void displayRect();

	// May need to be overrided
	bool checkBorderCollision();
};

#endif // !RIGIDRECT_H

