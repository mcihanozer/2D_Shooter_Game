#ifndef CANNON_H
#define CANNON_H

#include "Common.h"
#include "MovingObject.h"

// MCO: Cannon object controlled by the player: Generated by GameManager
class Cannon : public MovingObject
{
public:
	Cannon(const int id, const float width, const float height, const float centX, const float centY,
		unsigned int red = 0, unsigned int green = 0, unsigned int blue = 255);
	~Cannon();


	void displaySelf();
	void move() {}
	void setVertices();

	void turn(const eDirection dir);
	void rotate();

	Vec2 getTransformedCenter();
	Vec2 getLookDirection();

private:

	float mTheta;	// Rotation angle

	Vec2 mPivot;

	std::vector<Vec2> mTransformedVertices;
};

#endif 

