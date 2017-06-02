#include "time.h"
#include "graphics.h"

#undef UNICODE
#include <windows.h>

#include "Common.h"

#include "C_Application.h"


// Global variables

//C_Application::T_PressedKey g_PressedKeys = 0;
T_PressedKey g_PressedKeys = 0;


const int screenWidth  = 800;
const int screenHeight = 600;


//----------------------------
//----------------------------


static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		FillRect(0, 0, screenWidth, screenHeight, 0);
		break;
	case WM_KEYDOWN:
		switch(wParam)
		{
		// MCO: Because Common.h was introduced
		//case VK_LEFT:  g_PressedKeys |= C_Application::s_KeyLeft;  break;
		//case VK_UP:    g_PressedKeys |= C_Application::s_KeyUp;    break;
		//case VK_RIGHT: g_PressedKeys |= C_Application::s_KeyRight; break;
		//case VK_DOWN:  g_PressedKeys |= C_Application::s_KeyDown;  break;
		//case VK_SPACE: g_PressedKeys |= C_Application::s_KeySpace; break;
		case VK_LEFT:  g_PressedKeys |= s_KeyLeft;  break;
		case VK_UP:    g_PressedKeys |= s_KeyUp;    break;
		case VK_RIGHT: g_PressedKeys |= s_KeyRight; break;
		case VK_DOWN:  g_PressedKeys |= s_KeyDown;  break;
		case VK_SPACE: g_PressedKeys |= s_KeySpace; break;
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_KEYUP:
		switch(wParam)
		{
		// MCO: Because Common.h was introduced
		//case VK_LEFT:  g_PressedKeys &= ~C_Application::s_KeyLeft;  break;
		//case VK_UP:    g_PressedKeys &= ~C_Application::s_KeyUp;    break;
		//case VK_RIGHT: g_PressedKeys &= ~C_Application::s_KeyRight; break;
		//case VK_DOWN:  g_PressedKeys &= ~C_Application::s_KeyDown;  break;
		//case VK_SPACE: g_PressedKeys &= ~C_Application::s_KeySpace; break;
		case VK_LEFT:  g_PressedKeys &= ~s_KeyLeft;  break;
		case VK_UP:    g_PressedKeys &= ~s_KeyUp;    break;
		case VK_RIGHT: g_PressedKeys &= ~s_KeyRight; break;
		case VK_DOWN:  g_PressedKeys &= ~s_KeyDown;  break;
		case VK_SPACE: g_PressedKeys &= ~s_KeySpace; break;
		}
		break;
	}
	
	return DefWindowProc(hwnd, msg, wParam, lParam);
}


//----------------------------
//----------------------------


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Initialize graphics library
	// *** do not remove ***
	s_init	init;
	memset(&init, 0, sizeof(init));

	init.captionText  = "MCO | 2D Shooter Game ";
	init.instance     = hInstance;
	init.wndProc      = WndProc;
	init.screenWidth  = screenWidth;
	init.screenHeight = screenHeight;

	HWND hwndMain = InitializeGraphics( init );
	
	// Clear screen
	FillRect(0, 0, screenWidth, screenHeight, 0);
	
	{
		C_Application app(screenWidth, screenHeight);
		DWORD lastTime = timeGetTime();
		
		// Main game loop

		while(true)
		{
			// Pause kSleepTimeMs milliseconds

			const DWORD kSleepTimeMs = 20;			
			const DWORD currentTime = timeGetTime();
			const DWORD timeSinceLast = currentTime - lastTime;

			if (timeSinceLast < kSleepTimeMs)
			{
				Sleep(kSleepTimeMs - timeSinceLast);
			}

			lastTime = currentTime;			

			// Windows messaging
			// *** do not remove ***
			MSG msg;
			if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if(msg.message==WM_QUIT)
				{
					break;
				}
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}


			app.Tick(g_PressedKeys);

		}
	}

	// Uninitialize graphics
	// *** do not remove ***
	UninitializeGraphics();

	return 0;
}
