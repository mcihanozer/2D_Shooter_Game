#include "Grid.h"

#include <algorithm>

// Helper class. If we have rigid bodies that occupy more than one grid, IdHandler is used to prevent
// to collide them more than once.
class IdHandler
{
public:

	// Check whether the id pairs are collided before in that frame
	static bool checkIds(int idI, int idII)
	{
		if (idI > idII)
		{
			std::swap(idI, idII);
		}


		for (std::vector<std::pair<int, int>>::iterator it = sortedPairs.begin(); it != sortedPairs.end(); it++)
		{
			if (idI < it->first || (idI == it->first && idII < it->second))
			{
				sortedPairs.insert(it, std::make_pair(idI, idII));
				return false;
			}
			else if (idI == it->first && idII == it->second)
			{
				return true;
			}
		}

		sortedPairs.push_back(std::make_pair(idI, idII));
		return false;
	}

	static void refresh()
	{
		sortedPairs.clear();
	}


private:

	static std::vector<std::pair<int, int>> sortedPairs;
};
std::vector<std::pair<int, int>> IdHandler::sortedPairs;


Grid::Grid(const int cellSize)
{
	mCellSize = cellSize;

	mGrids = std::vector<std::vector<std::vector<RigidBody*>>>((SCREEN_HEIGHT / mCellSize));

	for (int row = 0; row < mGrids.size(); row++)
	{
		for (int col = 0; col < SCREEN_WIDTH / mCellSize; col++)
		{
			mGrids[row].push_back(std::vector<RigidBody*>());
		}
	}
}

Grid::~Grid()
{
	clear();
}

void Grid::insert(RigidBody* obj)
{
	// This code inserts a single rigid body into multiple grids if necessary

	int startRow = std::max(0, (int)(obj->getBBoxUp().y / mCellSize));
	int startCol = std::max(0, (int)(obj->getBBoxUp().x / mCellSize));
	int endRow = std::min((int)mGrids.size() - 1, (int)(obj->getBBoxDown().y / mCellSize));
	int endCol = std::min((int)mGrids[0].size() - 1, (int)(obj->getBBoxDown().x / mCellSize));

	// Insert into the grids
	for (int row = startRow; row <= endRow; row++)
	{
		for (int col = startCol; col <= endCol; col++)
		{
			mGrids[row][col].push_back(obj);
		}
	}
}

void Grid::testCollisions()
{
	// Keep id's of the collided objects } In this way, we can prevent multiple collision of
	// the same objects involving more than one grid cell

	for (int row = 0; row < mGrids.size(); row++)	// For each row of the grid
	{
		for (int col = 0; col < mGrids[row].size(); col++)	// For each column of the grid
		{
			if (mGrids[row][col].size() > 1)	// If there is more than one object in the current cell of the grid
			{
				for (int rbI = 0; rbI < mGrids[row][col].size(); rbI++)	// Check collision for the objects
				{
					for (int rbII = rbI + 1; rbII < mGrids[row][col].size(); rbII++)
					{
						if (mGrids[row][col].at(rbI)->checkCollision(mGrids[row][col].at(rbII)))
						{
							if (!IdHandler::checkIds(mGrids[row][col].at(rbI)->getId(), mGrids[row][col].at(rbII)->getId()))
							{
								// COLLISION IS HAPPENING
								mGrids[row][col].at(rbI)->setCollided();
								mGrids[row][col].at(rbII)->setCollided();

								mGrids[row][col].at(rbI)->collide(mGrids[row][col].at(rbII)->getBodyType());
								mGrids[row][col].at(rbII)->collide(mGrids[row][col].at(rbI)->getBodyType());
							}

						}
					}
				}
			}
		}
	}

	IdHandler::refresh();
}

void Grid::clear()
{
	for (int row = 0; row < mGrids.size(); row++)
	{
		for (int col = 0; col < SCREEN_WIDTH / mCellSize; col++)
		{
			mGrids[row][col].clear();
		}
	}
}