#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Cannon.h"
#include "Grid.h"
#include "Renderer.h"

// GameManager constructs the level by initializing the objects (Clock and Cannon), updates the frames,
// starts collision detection, and calls Renderer to render the frame. It also handles KeyManager
// role at this point to rotate the Cannon or initializing the bullets.

// TODO Increase decoupling:
// - Introduce key manager to handle the keys
// - Introduce observers } Sent event to Cannon to rotate itself, generate and add bullets using events (observer and
//   key manager together), etc.
// - Introduce Stage
class GameManager
{
public:
	GameManager();
	~GameManager();

	void init();

	bool checkGameOverCase();
	void restart();

	// Called at the begining of the frame
	void callFrameBegining(const T_PressedKey pressedKeys);
	void render();
	void callFrameEnd();

private:

	void generateNpc();
	void generateNpc(const float width, const float height);
	void generateNpc(const float width, const float height, const float centX, const float centY);
	bool createLevel();

	void updateObjects();
	void updateStage();

	// TODO Replace with a key manager and also introduce event and observers
	void handleKey(const T_PressedKey pressedKeys);

	unsigned int mNpcCounter;

	Renderer* mRenderer;
	Grid* mGrid;

	std::vector<Cannon*> mPlayerList;
	std::vector<RigidBody*> mAIList;

	// For minimizing memory allocation
	// TODO Actually allocate some amount of NPC (Just Clock at this point) and Bullets while constructing
	// the level
	std::vector<RigidBody*> mUsedBullet;
	std::vector<RigidBody*> mUsedNpc;

};

#endif // !GAMEMANAGER_H
