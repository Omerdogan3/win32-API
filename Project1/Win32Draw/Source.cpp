#include "resource.h"

#ifndef UNICODE
#define UNICODE
#endif 

#define MAXPOINTS 1000

#include <iostream>
#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int isInCircle(POINT p);
int isInRectangle(POINT p);

HWND textField;
PAINTSTRUCT ps;
HFONT font;
HDC hdc;
int r = 20, g = 10, b = 10, s = 10;
POINT rectPoints[MAXPOINTS];
POINT cirPoints[MAXPOINTS];
POINT p;
int recCount = 0;
int cirCount = 0;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	// Register the window class.
	const wchar_t CLASS_NAME[] = L"Sample Window Class";
	
	WNDCLASS wc = {};

	wc.lpszMenuName = MAKEINTRESOURCE(MYMENU);
	wc.hIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON2), IMAGE_ICON, 16, 16, 0);

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	// Create the window.

	HWND hwnd = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		L"Drawn by Omer Dogan",    // Window text
		WS_OVERLAPPEDWINDOW | WS_VSCROLL,           // Window style

													// Size and position
		300, 150, 500, 500,

		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
	);

	if (hwnd == NULL)
	{
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);


	// Run the message loop.

	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	RECT rect;
	int up, down, left, right;
	GetWindowRect(hwnd, &rect);
	
	

	char str[150];
	switch (uMsg)
	{

	case WM_COMMAND:
		if (LOWORD(wParam) == ID_QUIT)
		{
			DestroyWindow(hwnd);
		}
		else if (LOWORD(wParam) == ID_CLEARSCREEN)
		{
			HDC hDC;
			HPEN hPen;
			HBRUSH hBrush;
			HGDIOBJ hOldPen, hOldBrush;
			/* draw a red-bordered, cyan-filled rectangle */
			hDC = GetDC(hwnd);                /* get a DC for painting */
			hPen = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));   /* pen */
			hBrush = CreateSolidBrush(RGB(255, 255, 255));  /* brush */
			hOldPen = (HPEN)SelectObject(hDC, hPen);      /* select into DC & */
			hOldBrush = (HBRUSH)SelectObject(hDC, hBrush); /* save old object */
			Rectangle(hDC, 0, 0, 500, 500);        /* draw rectangle */
			SelectObject(hDC, hOldBrush);          /* displace new brush */
			DeleteObject(hBrush);                  /* delete it from DC */
			SelectObject(hDC, hOldPen);            /* same for pen */
			DeleteObject(hPen);
			ReleaseDC(hwnd, hDC);                   /* get rid of DC */

			recCount = 0;
			cirCount = 0;

				
		}
		else if (LOWORD(wParam) == ID_CIRCLE)
		{
			HDC hDC;
			HPEN hPen;
			HBRUSH hBrush;
			HGDIOBJ hOldPen, hOldBrush;

			up = rand() % 360 + 1;
			down = up + 80;
			left = rand() % 385 + 1;
			right = left + 80;


			/* draw a blue-bordered magenta-crosshatched circle */
			hDC = GetDC(hwnd);                 /* get a DC for painting */
			hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));  /* blue pen */
			hBrush = CreateHatchBrush(HS_DIAGCROSS, RGB(255, 0, 255));
			hOldPen = (HPEN)SelectObject(hDC, hPen);      /* select into DC & */
			hOldBrush = (HBRUSH)SelectObject(hDC, hBrush); /* save old object */
			Ellipse(hDC, left,up,right,down);       /* draw circle */
			SelectObject(hDC, hOldBrush);          /* displace brush */
			DeleteObject(hBrush);                  /* delete brush */
			SelectObject(hDC, hOldPen);            /* same for pen */
			DeleteObject(hPen);
			ReleaseDC(hwnd, hDC);   /* release the DC to end painting */

			cirPoints[cirCount].x = left;
			cirPoints[cirCount].y = up;
			cirCount++;
		}
		else if (LOWORD(wParam) == ID_RECTANGLE)
		{
			HDC hDC;
			HPEN hPen;
			HBRUSH hBrush;
			HGDIOBJ hOldPen, hOldBrush;

			up = rand() % 392 + 1;
			down = up + 45;
			left = rand() % 400 + 1;
			right = left + 65;

			/* draw a red-bordered, cyan-filled rectangle */
			hDC = GetDC(hwnd);                /* get a DC for painting */
			hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));   /* red pen */
			hBrush = CreateSolidBrush(RGB(0, 255, 255));  /* cyan brush */
			hOldPen = (HPEN)SelectObject(hDC, hPen);      /* select into DC & */
			hOldBrush = (HBRUSH)SelectObject(hDC, hBrush); /* save old object */
			Rectangle(hDC, left,up,right,down);        /* draw rectangle */
			SelectObject(hDC, hOldBrush);          /* displace new brush */
			DeleteObject(hBrush);                  /* delete it from DC */
			SelectObject(hDC, hOldPen);            /* same for pen */
			DeleteObject(hPen);
			ReleaseDC(hwnd, hDC);                   /* get rid of DC */

			rectPoints[recCount].x = left;
			rectPoints[recCount].y = up;
			recCount++;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_LBUTTONDOWN:
		// get the x and y coordinates
		
		p.x = LOWORD(lParam);
		p.y = HIWORD(lParam);

		

		break;

	case WM_LBUTTONUP:
		POINT p2;
		p2.x = LOWORD(lParam);
		p2.y = HIWORD(lParam);

		int cirStatus = isInCircle(p);
		int rectStatus = isInRectangle(p);
		if (cirStatus != -1)
		{
			HDC hDC;
			HPEN hPen;
			HBRUSH hBrush;
			HGDIOBJ hOldPen, hOldBrush;

			up = cirPoints[cirStatus].y;
			down = up + 80;
			left = cirPoints[cirStatus].x;
			right = left + 80;


			/* draw a blue-bordered magenta-crosshatched circle */
			hDC = GetDC(hwnd);                 /* get a DC for painting */
			hPen = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));  /* blue pen */
			hBrush = CreateHatchBrush(HS_DIAGCROSS, RGB(255, 255, 255));
			hOldPen = (HPEN)SelectObject(hDC, hPen);      /* select into DC & */
			hOldBrush = (HBRUSH)SelectObject(hDC, hBrush); /* save old object */
			Ellipse(hDC, left, up, right, down);       /* draw circle */
			SelectObject(hDC, hOldBrush);          /* displace brush */
			DeleteObject(hBrush);                  /* delete brush */
			SelectObject(hDC, hOldPen);            /* same for pen */
			DeleteObject(hPen);
			ReleaseDC(hwnd, hDC);   /* release the DC to end painting */


			up = p2.y;
			down = up + 80;
			left = p2.x;
			right = left + 80;


			/* draw a blue-bordered magenta-crosshatched circle */
			hDC = GetDC(hwnd);                 /* get a DC for painting */
			hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));  /* blue pen */
			hBrush = CreateHatchBrush(HS_DIAGCROSS, RGB(255, 0, 255));
			hOldPen = (HPEN)SelectObject(hDC, hPen);      /* select into DC & */
			hOldBrush = (HBRUSH)SelectObject(hDC, hBrush); /* save old object */
			Ellipse(hDC, left, up, right, down);       /* draw circle */
			SelectObject(hDC, hOldBrush);          /* displace brush */
			DeleteObject(hBrush);                  /* delete brush */
			SelectObject(hDC, hOldPen);            /* same for pen */
			DeleteObject(hPen);
			ReleaseDC(hwnd, hDC);   /* release the DC to end painting */

			cirPoints[cirCount].x = left;
			cirPoints[cirCount].y = up;
			cirCount++;
		}
		if (rectStatus != -1)
		{
			HDC hDC;
			HPEN hPen;
			HBRUSH hBrush;
			HGDIOBJ hOldPen, hOldBrush;

			up = rectPoints[rectStatus].y;
			down = up + 45;
			left = rectPoints[rectStatus].x;
			right = left + 65;

			/* draw a red-bordered, cyan-filled rectangle */
			hDC = GetDC(hwnd);                /* get a DC for painting */
			hPen = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));   /* red pen */
			hBrush = CreateSolidBrush(RGB(255, 255, 255));  /* cyan brush */
			hOldPen = (HPEN)SelectObject(hDC, hPen);      /* select into DC & */
			hOldBrush = (HBRUSH)SelectObject(hDC, hBrush); /* save old object */
			Rectangle(hDC, left, up, right, down);        /* draw rectangle */
			SelectObject(hDC, hOldBrush);          /* displace new brush */
			DeleteObject(hBrush);                  /* delete it from DC */
			SelectObject(hDC, hOldPen);            /* same for pen */
			DeleteObject(hPen);
			ReleaseDC(hwnd, hDC);                   /* get rid of DC */

			

			up = p2.y;
			down = up + 45;
			left = p2.x;
			right = left + 65;

			/* draw a red-bordered, cyan-filled rectangle */
			hDC = GetDC(hwnd);                /* get a DC for painting */
			hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));   /* red pen */
			hBrush = CreateSolidBrush(RGB(0, 255, 255));  /* cyan brush */
			hOldPen = (HPEN)SelectObject(hDC, hPen);      /* select into DC & */
			hOldBrush = (HBRUSH)SelectObject(hDC, hBrush); /* save old object */
			Rectangle(hDC, left, up, right, down);        /* draw rectangle */
			SelectObject(hDC, hOldBrush);          /* displace new brush */
			DeleteObject(hBrush);                  /* delete it from DC */
			SelectObject(hDC, hOldPen);            /* same for pen */
			DeleteObject(hPen);
			ReleaseDC(hwnd, hDC);                   /* get rid of DC */

			rectPoints[recCount].x = left;
			rectPoints[recCount].y = up;
			recCount++;


		}




		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int isInRectangle(POINT p)
{
	for (int i = 0; i < recCount; i++)
	{
		if ((p.x >= rectPoints[i].x && p.x <= rectPoints[i].x + 65) && (p.y >= rectPoints[i].y && p.y <= rectPoints[i].y + 45))
		{
			return i;
		}
	}
	return -1;
}

int isInCircle(POINT p)
{
	for (int i = 0; i < cirCount; i++)
	{
		if ((p.x >= cirPoints[i].x && p.x <= cirPoints[i].x + 65) && (p.y >= cirPoints[i].y && p.y <= cirPoints[i].y + 45))
		{
			return i;
		}
	}
	return -1;
}