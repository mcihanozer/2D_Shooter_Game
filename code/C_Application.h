#ifndef TEST_C_APPLICATION_H
#define TEST_C_APPLICATION_H

#include "GameManager.h"

//TODO LIST
// - Increase decoupling in GameManager class } Introduce events, observer, and key manager
// - Introduce face, vertex, etc. information and Stage } That will make Renderer class better, but not
//   so crucial for this project since the scope is small

class C_Application
{
public:
	
	//typedef unsigned int T_PressedKey; // MCO: it is moved to Common.h since GameManager also needs it

	C_Application(int screenWidth, int screenHeight);
	~C_Application();

	/// Tick is called on fix framerate (50fps)
	void Tick(T_PressedKey pressedKeys);

	// MCO: it is moved to Common.h since GameManager also needs it
	//static const T_PressedKey s_KeyLeft  = 0x01;
	//static const T_PressedKey s_KeyUp    = 0x02;
	//static const T_PressedKey s_KeyRight = 0x04;
	//static const T_PressedKey s_KeyDown  = 0x08;
	//static const T_PressedKey s_KeySpace = 0x10;

private:
	const int	m_ScreenWidth;
	const int	m_ScreenHeight;

	GameManager* mManager;
};

#endif // #ifndef TEST_C_APPLICATION_H
