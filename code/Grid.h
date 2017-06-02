#ifndef GRID_H
#define GRID_H

#include "Common.h"

#include "Clock.h"

// Uniform grid for collision detection.

// Scope of this project does not mind whether there is a brute-force or "smart" collising
// detection handling. But, it is good to have it before hand in case of number of rigid bodies will increase.
// Plus, very same grid can also be used for rendering by making small changes.

// Why uniform grid?
// BVH: We have many objects moving all around during the frames. Constructing BVH for each frame would be very costly.
// Spatial partitioning techniques are better and more suitable since our borders are exact and static. Thus, we can
// easily construct our hierarchy based on object positions for each frame really fast.

//BSP: Good for indoor games (such as Quake) and collision detections between level geometry and game level } This are
// not really the case for this game, so BSP is not suitable.

// Quadtree and Unifrom grid are very suitable of this game's design. However, uniform grid is easier to handle and construct
// than quadtree since all the rigid bodies we have move all around the screen (a "large open space").
class Grid
{
public:
	Grid(const int cellSize);
	~Grid();

	// Insert rigid-body to the grid
	void insert(RigidBody* obj);

	void testCollisions();

	// Clear the grid objects for the next frame
	void clear();


private:
	// TODO Maybe use a 2D array?
	std::vector<std::vector<std::vector<RigidBody*>>> mGrids;

	int mCellSize;
};


#endif // !GRID_H
