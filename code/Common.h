#ifndef COMMON_H
#define COMMON_H

#include <math.h>

#include "Geometry.h"

// MCO: Keep common information needed all around the program.
// Since scope of this project is really small, this kind of header file is enough.

#define CLOCK_SIZE 100
#define GRID_SIZE	CLOCK_SIZE // ASSUMPTION: There will be no object (i.e. Clock) greater than GRID_SIZE x GRID_SIZE

// TODO When a Stage object introduced, these won't be needed as global
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

typedef unsigned int T_PressedKey;

static const T_PressedKey s_KeyLeft = 0x01;
static const T_PressedKey s_KeyUp = 0x02;
static const T_PressedKey s_KeyRight = 0x04;
static const T_PressedKey s_KeyDown = 0x08;
static const T_PressedKey s_KeySpace = 0x10;

const float PI = 3.1415926536f;

enum eRigidBodyType { eBox, eBullet, eClock };
enum eDirection { eUp, eRight, eDown, eLeft};

extern float toRadian(const float degree);
// Rotation of a point about an arbitrary point (Pivot point)
extern void rotateAroundPivot(float& rotX, float& rotY, const float pivotX, const float pivotY, const float theta);
extern Vec2 getRandomDirection();
extern void getRandomDirection(Vec2& dir);

#endif // !COMMON_H

