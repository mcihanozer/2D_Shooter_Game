#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "MovingObject.h"

#include "Common.h"

// Base class for rigid bodies. RigidBody is a movable object that can be collide with
// other RigidBody objects and screen borders.
class RigidBody : public MovingObject
{
public:

	RigidBody() {}

	RigidBody(const int id, const unsigned int color, const float width, const float height);

	RigidBody(const int id, const unsigned int color, const float width, const float height,
			  const float centX, const float centY);

	RigidBody(const int id, const unsigned int color, const float width, const float height,
		const float centX, const float centY, const float moveDirX, const float movedirY, eRigidBodyType type);

	virtual bool checkCollision(const RigidBody* obj) const = 0;
	virtual void collide(const eRigidBodyType type) = 0;
	virtual const Vec2& getBBoxUp() const = 0;
	virtual const Vec2& getBBoxDown() const = 0;

	virtual const eRigidBodyType getBodyType() const;
	virtual const bool isCollided() const;
	virtual void setCollided();
	virtual void revertCollided();

	virtual const bool isAlive() const;
	virtual void revive();
	virtual void setDead();
	virtual const bool canRevive() const;
	virtual void setCantRevive();

protected:

	virtual void init();

	virtual bool checkBorderCollision() = 0;

	bool mIsCollided;
	bool mIsAlive;
	bool mCanRevive;

	eRigidBodyType mRigidBodyType;
};

#endif // !RIGIDBODY_H
