#ifndef TEST_GRAPHICS_H
#define TEST_GRAPHICS_H


#undef UNICODE
#include <windows.h>


//get pixel color value from rgb components
inline unsigned int GetRGB(unsigned int r, unsigned int g, unsigned int b)
{
	return r + (g<<8) + (b<<16);
}


//draw filled rectangle
void FillRect(int x, int y, int sx, int sy, unsigned int color);

//draw line
void DrawLine(int x1, int y1, int x2, int y2, unsigned int color);









// FOR INTERNAL TEST USAGE

struct s_init
{
	HINSTANCE		instance;
	WNDPROC			wndProc;
	const char*		captionText;
	int				screenWidth;
	int				screenHeight;
};

// Initialize graphics "library"
HWND InitializeGraphics(const s_init&);

// Uninitialize graphics "library"
void UninitializeGraphics();



#endif // #ifndef TEST_GRAPHICS_H
