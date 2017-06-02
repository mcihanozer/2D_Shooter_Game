#include "GameManager.h"

#include"Bullet.h"

#include <queue>

#define BULLET_WIDTH 1
#define BULLET_HEIGHT 4

#define TEST_LEVEL_ENEMY_NUM 2

#define CANNON_WIDTH 20
#define CANNON_HEIGHT 30
#define CANNON_WIDTH_PER 0.5
#define CANNON_HEIGHT_PER  0.9

// Helper Class: Keep tracks of the unique IDs of GameObjects
class IdManager
{
public:

	static void init()
	{
		nextId = 0;
	}

	static int getId()
	{
		if (idQueue.empty())
		{
			return nextId++;
		}
		
		int id = idQueue.front();
		idQueue.pop();
		return id;
	}

	static void giveIdBack(const int id)
	{
		idQueue.push(id);
	}

	static void reset()
	{
		init();
		std::queue<int> empty;
		std::swap(idQueue, empty);
	}

private:

	static int nextId;
	static std::queue<int> idQueue;
};
std::queue<int> IdManager::idQueue;
int IdManager::nextId;

GameManager::GameManager()
{
	IdManager::init();

	mNpcCounter = 0;

	mRenderer = new Renderer();

	mGrid = new Grid(GRID_SIZE);
}

GameManager::~GameManager()
{
	delete mRenderer;

	mGrid->clear();
	delete mGrid;

	for (int ci = 0; ci < mAIList.size(); ci++)
	{
		delete mAIList[ci];
	}
	mAIList.clear();

	for (int ci = 0; ci < mPlayerList.size(); ci++)
	{
		delete mPlayerList[ci];
	}
	mPlayerList.clear();

	for (int ci = 0; ci < mUsedBullet.size(); ci++)
	{
		delete mUsedBullet[ci];
	}
	mUsedBullet.clear();

	for (int ci = 0; ci < mUsedNpc.size(); ci++)
	{
		delete mUsedNpc[ci];
	}
	mUsedNpc.clear();
}

void GameManager::init()
{
	// In a real game, this would be the line the level information will be read
	// and the level will be constructed
	createLevel();
}

void GameManager::generateNpc(const float width, const float height)
{
	if (mUsedNpc.size() > 0)
	{
		// TODO Maybe make a method since you also use it in generateNpc(width, height, centX, centY)?
		mUsedNpc.back()->setWidth(width);
		mUsedNpc.back()->setHeight(height);
		mUsedNpc.back()->setCenterRandomly();
		mUsedNpc.back()->revive();
		mAIList.push_back(mUsedNpc.back());
		mUsedNpc.pop_back();
	}
	else
	{
		mAIList.push_back(new Clock(IdManager::getId(), width, height));
	}

	mNpcCounter++;
}

void GameManager::generateNpc(const float width, const float height, const float centX, const float centY)
{
	if (mUsedNpc.size() > 0)
	{
		// TODO Maybe make a method since you also use it in generateNpc(width, height)?
		mUsedNpc.back()->setWidth(width);
		mUsedNpc.back()->setHeight(height);
		mUsedNpc.back()->setPosition(centX, centY);
		mUsedNpc.back()->revive();
		mAIList.push_back(mUsedNpc.back());
		mUsedNpc.pop_back();
	}
	else
	{
		mAIList.push_back(new Clock(IdManager::getId(), width, height, centX, centY));
	}

	mNpcCounter++;
}

void GameManager::generateNpc()
{
	generateNpc(CLOCK_SIZE, CLOCK_SIZE);
}

bool GameManager::createLevel()
{
	// Construct the rest of the level

	// TODO In a real game, this would be the line the level information will be read
	// and the level will be constructed. So, make this better (more generic) when you introduce Level system
	for (int ei = 0; ei < TEST_LEVEL_ENEMY_NUM; ei++)
	{
		generateNpc();
	}


	mPlayerList.push_back(new Cannon(IdManager::getId(), CANNON_WIDTH, CANNON_HEIGHT,
									(SCREEN_WIDTH * CANNON_WIDTH_PER), (SCREEN_HEIGHT * CANNON_HEIGHT_PER)));

	return true;
}

bool GameManager::checkGameOverCase()
{
	return !(mNpcCounter > 0);
}

// Restart the same level
void GameManager::restart()
{
	// TODO Make this better (more generic) when you introduce Level system
	IdManager::reset();

	mGrid->clear();

	for (int ci = mAIList.size() - 1; ci > -1; ci--)
	{
		if (mAIList[ci]->getBodyType() == eRigidBodyType::eClock)
		{
			mUsedNpc.push_back(mAIList[ci]);
		}
		else
		{
			mUsedBullet.push_back(mAIList[ci]);
		}

		mAIList.erase(mAIList.begin() + ci);
	}
	mAIList.clear();
	mNpcCounter = 0;

	for (int ei = 0; ei < TEST_LEVEL_ENEMY_NUM; ei++)
	{
		generateNpc();
	}
}

void GameManager::handleKey(const T_PressedKey pressedKeys)
{
	// TODO Increase decoupling

	// TODO Since it is single player...
	if (pressedKeys & s_KeyLeft)
	{
		//for (int pi = 0; pi < mPlayerList.size(); pi++)
		//{
		//
		//}

		mPlayerList[0]->turn(eDirection::eLeft);
	}

	// TODO Since it is single player...
	if (pressedKeys & s_KeyRight)
	{
		//for (int pi = 0; pi < mPlayerList.size(); pi++)
		//{
		//
		//}

		mPlayerList[0]->turn(eDirection::eRight);
	}

	// TODO Since it is single player...
	if (pressedKeys & s_KeySpace)
	{
		Vec2 pos = mPlayerList[0]->getTransformedCenter();
		Vec2 dir = mPlayerList[0]->getLookDirection();

		if (mUsedBullet.size() > 0)
		{
 			mUsedBullet.back()->setPosition(pos);
			mUsedBullet.back()->setDirection(dir);
			mUsedBullet.back()->revive();
			mAIList.push_back(mUsedBullet.back());
			mUsedBullet.pop_back();
		}
		else
		{
			mAIList.push_back(new Bullet(IdManager::getId(), BULLET_WIDTH, BULLET_HEIGHT, pos.x, pos.y, dir.x, dir.y));
		}
		
	}
}

void GameManager::updateObjects()
{
	// Make moves and fill the grid
	for (int ci = 0; ci < mAIList.size(); ci++)
	{
		mAIList[ci]->move();
		mGrid->insert(mAIList[ci]);
	}
}

void GameManager::updateStage()
{
	// Update the stage by handling the collision results:
	// - Removal from the scene
	// - Getting shot
	// etc.

	// Update the lists
	std::vector<int> removeObjects;

	// TODO Increase decoupling
	for (int ai = 0; ai < mAIList.size(); ai++)
	{
		if (!mAIList[ai]->isAlive())
		{
			if (mAIList[ai]->getBodyType() == eRigidBodyType::eBullet)
			{
				// Put into used bullet box
				removeObjects.push_back(ai);
				mUsedBullet.push_back(mAIList[ai]);
			}
			else if (mAIList[ai]->getBodyType() == eRigidBodyType::eClock)
			{
				if (mAIList[ai]->canRevive())
				{
					Vec2 center = mAIList[ai]->getCenter();
					float width = mAIList[ai]->getWidth();
					float height = mAIList[ai]->getHeight();

					// Divide half
					mAIList[ai]->setWidth(width * 0.5f);
					mAIList[ai]->setHeight(height * 0.5f);
					mAIList[ai]->setPosition(Vec2(mAIList[ai]->getCenter().x - (mAIList[ai]->getWidth() * 0.5f), mAIList[ai]->getCenter().y - (mAIList[ai]->getHeight() * 0.5f)));
					mAIList[ai]->revive();

					// 2nd
					generateNpc(width * 0.5f, height * 0.5f, (center.x + (width * 0.25f)), (center.y + (height * 0.25f)));

				}
				else
				{
					mUsedNpc.push_back(mAIList[ai]);
					removeObjects.push_back(ai);
					mNpcCounter--;
				}
			}
		}
	}

	for (int i = removeObjects.size() - 1; i > -1; i--)
	{
		mAIList.erase(mAIList.begin() + removeObjects[i]);
	}
}

void GameManager::callFrameBegining(const T_PressedKey pressedKeys)
{
	// Call renderer to clean the screen
	mRenderer->refresh();

	// Take the user input
	handleKey(pressedKeys);

	// Make moves and fill the grid
	updateObjects();

	// Make collisions
	mGrid->testCollisions();

	// Update the stage (asynchronous) 
	updateStage();
}

void GameManager::render()
{
	// Tell renderer to display everything
	std::vector<GameObject*> displayList;
	displayList.insert(displayList.end(), mAIList.begin(), mAIList.end());
	displayList.insert(displayList.end(), mPlayerList.begin(), mPlayerList.end());
	mRenderer->render(displayList);
}

void GameManager::callFrameEnd()
{
	mGrid->clear();
}