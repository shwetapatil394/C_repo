#include <Windows.h>

#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	static TCHAR szClassName[] = TEXT("Rowwise Columnwise Print");
	static TCHAR szWindowCaption[] = TEXT("Shweta Patil Task 4");

	HWND hWnd = NULL;
	HCURSOR hCursor = NULL;
	HICON hIcon = NULL;
	HICON hIconSm = NULL;
	HBRUSH hBrush = NULL;

	WNDCLASSEX wndEx;
	MSG msg;

	ZeroMemory(&wndEx, sizeof(WNDCLASSEX));
	ZeroMemory(&msg, sizeof(MSG));

	hBrush = (HBRUSH)GetStockObject(GRAY_BRUSH);
	if(!hBrush)
	{
		MessageBox((HWND)NULL, TEXT("Failed to obtain brush"), TEXT("GetStockObject"), MB_ICONERROR);
		return(EXIT_FAILURE);
	}
	hCursor = LoadCursor((HINSTANCE)NULL, IDC_ARROW);
	if(!hCursor)
	{
		MessageBox((HWND)NULL, TEXT("Failed to obtain cursor"), TEXT("LoadCursor"), MB_ICONERROR);
		return(EXIT_FAILURE);
	}
	hIcon = LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);
	if(!hIcon)
	{
		MessageBox((HWND)NULL, TEXT("Failed to load icon"), TEXT("LoadIcon"), MB_ICONERROR);
		return(EXIT_FAILURE);
	}
	hIconSm = LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);
	if(!hIconSm)
	{
		MessageBox((HWND)NULL, TEXT("Failed to load small icon"), TEXT("LoadIcon"), MB_ICONERROR);
		return(EXIT_FAILURE);
	}

	wndEx.cbSize = sizeof(WNDCLASSEX);
	wndEx.cbClsExtra = 0;
	wndEx.cbWndExtra = 0;
	wndEx.hbrBackground = hBrush;
	wndEx.hCursor = hCursor;
	wndEx.hIcon = hIcon;
	wndEx.hIconSm = hIconSm;
	wndEx.lpszClassName = szClassName;
	wndEx.lpszMenuName = NULL;
	wndEx.lpfnWndProc = WndProc;
	wndEx.hInstance = hInstance;
	wndEx.style = CS_VREDRAW | CS_HREDRAW;

	if(!RegisterClassEx(&wndEx))
	{
		MessageBox((HWND)hWnd, TEXT("Failed to register class"), TEXT("RegisterClassEx"), MB_ICONERROR);
		return(EXIT_FAILURE);
	}

	hWnd = CreateWindowEx(WS_EX_APPWINDOW, szClassName, szWindowCaption, WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
							(HWND)NULL, (HMENU)NULL, hInstance, NULL);
	if(!hWnd)
	{
		MessageBox((HWND)NULL, TEXT("Failed to create window"), TEXT("CreateWindowEX"), MB_ICONERROR);
		return(EXIT_FAILURE);
	}

	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);

	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int xPos = 0, yPos = 0, iCounter = 0;

	static int iNoOfCol, iNoOfRow;
	static int cxChar, cyChar, cxClient, cyClient;

	HDC hdc;
	TEXTMETRIC tm;
	PAINTSTRUCT ps;

	switch(uMsg)
	{
		case WM_CREATE:
			hdc = GetDC(hWnd);
			GetTextMetrics(hdc, &tm);
			cxChar = tm.tmAveCharWidth;
			cyChar = tm.tmHeight + tm.tmExternalLeading;
			ReleaseDC(hWnd, hdc);
			break;

		case WM_SIZE:
			cxClient = LOWORD(lParam);
			cyClient = HIWORD(lParam);
			iNoOfCol = cxClient / cxChar;
			iNoOfRow = cyClient / cyChar;
			break;

		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			xPos = 0;
			yPos = 0;
			for(iCounter = 0; iCounter < iNoOfCol/2; ++iCounter)
			{
				TextOut(hdc, xPos, yPos, TEXT("C"), lstrlen("C"));
				xPos = xPos + (cxChar * 2);
			}
			xPos = 0;
			yPos = 0;
			for(iCounter = 0; iCounter < iNoOfRow; ++iCounter)
			{
				TextOut(hdc, xPos, yPos, TEXT("R"), lstrlen("R"));
				yPos = yPos + cyChar;
			}
			EndPaint(hWnd, &ps);
			break;

		case WM_DESTROY:
			PostQuitMessage(EXIT_SUCCESS);
			break;
	}
	return(DefWindowProc(hWnd, uMsg, wParam, lParam));
}