#include "graphics.h"


static HWND g_Hwnd;


//draw filled rectangle
void FillRect(int x, int y, int sx, int sy, unsigned int color)
{
	HDC hdc = GetDC(g_Hwnd);
	HBRUSH br = CreateSolidBrush(color);
	RECT rc;
	SetRect(&rc, x, y, x+sx, y+sy);
	FillRect(hdc, &rc, br);
	DeleteObject(br);
	ReleaseDC(g_Hwnd, hdc);
}


//draw line
void DrawLine(int x1, int y1, int x2, int y2, unsigned int color)
{
	HDC hdc = GetDC(g_Hwnd);
	HPEN pen = CreatePen(PS_SOLID, 1, color);
	HGDIOBJ old_pen = SelectObject(hdc, pen);

	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);

	SelectObject(hdc, old_pen);
	DeleteObject(pen);
	ReleaseDC(g_Hwnd, hdc);
}


//initialize "library"
HWND InitializeGraphics(const s_init& init)
{
	WNDCLASSEX wc;
	memset(&wc, 0, sizeof(wc));
	wc.cbSize        = sizeof(WNDCLASSEX);
	wc.lpfnWndProc   = init.wndProc;
	wc.hInstance     = init.instance;
	wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wc.lpszClassName = "MainWindow";
	RegisterClassEx(&wc);

	DWORD dw_style = WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_CLIPCHILDREN;
	RECT rc;
	SetRect(&rc, 0, 0, init.screenWidth, init.screenHeight);
	AdjustWindowRect(&rc, dw_style, false);
	rc.right  -= rc.left;
	rc.bottom -= rc.top;

	g_Hwnd = CreateWindowEx( 0,
		"MainWindow",           //ClassName
		init.captionText,
		dw_style | WS_VISIBLE,
		(GetSystemMetrics(SM_CXSCREEN)-rc.right)/2,
		(GetSystemMetrics(SM_CYSCREEN)-rc.bottom)/2,
		rc.right, rc.bottom,
		NULL,                   //hwndParent
		NULL,
		init.instance,
		NULL);                  //lpvParam

	return g_Hwnd;
}


// Uninitialize graphic "library"
void UninitializeGraphics()
{
	DestroyWindow(g_Hwnd);
}
