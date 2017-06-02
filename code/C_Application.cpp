#include "C_Application.h"

C_Application::C_Application(int screenWidth, int screenHeight)
	: m_ScreenWidth(screenWidth)
	, m_ScreenHeight(screenHeight)
{
	SCREEN_WIDTH = screenWidth;
	SCREEN_HEIGHT = screenHeight;

	mManager = new GameManager();
	mManager->init();
}


C_Application::~C_Application()
{
	delete mManager;
}

void C_Application::Tick(T_PressedKey pressedKeys)
{
	// Sample tick
	mManager->callFrameBegining(pressedKeys);

	mManager->render();

	if (mManager->checkGameOverCase())
	{
		// Apply game over case here
		mManager->restart();
	}

	mManager->callFrameEnd();
}
