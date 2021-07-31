#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

#define BUFFER_SIZE	256
#define SUCCESS	1

#define FAIL_EXIT_IF(cond, szCaption, szMessage)	do\
													{\
														if((cond))\
														{\
															MessageBox((HWND)NULL, TEXT(szMessage), TEXT(szCaption), MB_ICONERROR);\
															ReleaseAll();\
															ExitProcess(EXIT_FAILURE);\
														}\
													} while (0);\

// Vector of string information structure
typedef struct tagStringVector
{
	CHAR** pArrayOfStrings;
	UINT uNumberOfLines;
}VECTOR_OF_STRINGS, *P_VECTOR_OF_STRINGS, *NP_VECTOR_OF_STRINGS, *LP_VECTOR_OF_STRINGS;

// Vector APIs
P_VECTOR_OF_STRINGS CreateVectorOfStrings(void);
ATOM PushBackInVectorOfStrings(P_VECTOR_OF_STRINGS pVectorOfStrings, CHAR* szString);
ATOM DestroyVectorOfStrings(P_VECTOR_OF_STRINGS pVectorOfStrings);

// File reading function
P_VECTOR_OF_STRINGS ReadFileInMemory(LPSTR szFileName);

// Callback
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void ReleaseAll(void);

// Global data
LPSTR gszFileName = NULL;
P_VECTOR_OF_STRINGS gpLinesInFiles = NULL;
UINT g_uMaxLength;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	static TCHAR szClassName[] = TEXT("The standard window");
	static TCHAR szWindowCaption[] = TEXT("File Reader");

	HBRUSH hBrush = NULL;
	HCURSOR hCursor = NULL;
	HICON hIcon = NULL;
	HICON hIconSm = NULL;
	HWND hWnd = NULL;

	ATOM bIsWindowClassRegistered = 0;

	WNDCLASSEX wndEx;
	MSG msg;

	gszFileName = lpCmdLine;

	ZeroMemory(&wndEx, sizeof(WNDCLASSEX));
	ZeroMemory(&msg, sizeof(MSG));

	hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
	FAIL_EXIT_IF(hBrush == NULL, "GetStockObject", "Could not obtain brush");

	hCursor = LoadCursor((HINSTANCE)NULL, IDC_ARROW);
	FAIL_EXIT_IF(hCursor == NULL, "LoadCursor", "Could not load cursor");

	hIcon = LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);
	FAIL_EXIT_IF(hIcon == NULL, "LoadIcon", "Could not load icon");

	hIconSm = LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);
	FAIL_EXIT_IF(hIconSm == NULL, "LoadIcon", "Could not load small icon");

	wndEx.cbSize = sizeof(WNDCLASSEX);
	wndEx.cbClsExtra = 0;
	wndEx.cbWndExtra = 0;
	wndEx.hbrBackground = hBrush;
	wndEx.hCursor = hCursor;
	wndEx.hIcon = hIcon;
	wndEx.hIconSm = hIconSm;
	wndEx.hInstance = hInstance;
	wndEx.lpfnWndProc = WndProc;
	wndEx.lpszClassName = szClassName;
	wndEx.lpszMenuName = NULL;
	wndEx.style = CS_HREDRAW | CS_VREDRAW;

	bIsWindowClassRegistered = RegisterClassEx(&wndEx);
	FAIL_EXIT_IF(bIsWindowClassRegistered == 0, "RegisterClassEx", "Could not register window class");

	hWnd = CreateWindowEx(	WS_EX_APPWINDOW, szClassName, szWindowCaption,
							WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL,
							CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
							(HWND)NULL, (HMENU)NULL, hInstance, NULL );
	FAIL_EXIT_IF(hWnd == NULL, "CreateWindowEx", "Could not create a window");

	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);

	while(GetMessage(&msg, (HWND)NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	ReleaseAll();

	return(msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static int cxChar, cxCaps, cyChar, cxClient, cyClient, iMaxWidth;

	int i, x, y, iVertPos, iHorzPos, iPaintBeg, iPaintEnd;

	HDC hdc = NULL;
	TEXTMETRIC tm;
	PAINTSTRUCT ps;
	SCROLLINFO si;

	FILE* fp = NULL;

	switch(uMsg)
	{
		case WM_CREATE:
			hdc = GetDC(hWnd);
			GetTextMetrics(hdc, &tm);
			cxChar = tm.tmAveCharWidth;
			cyChar = tm.tmHeight + tm.tmExternalLeading;
			cxCaps = ((tm.tmPitchAndFamily & 1) ? 3 : 2) * (cxChar) / 2;
			ReleaseDC(hWnd, hdc);
			hdc = NULL;
			gpLinesInFiles = ReadFileInMemory(gszFileName);
			iMaxWidth = g_uMaxLength;
			break;

		case WM_SIZE:
			cxClient = LOWORD(lParam);
			cyClient = HIWORD(lParam);

			si.cbSize = sizeof(SCROLLINFO);
			si.fMask = SIF_RANGE | SIF_PAGE;
			si.nMin = 0;
			si.nMax = gpLinesInFiles->uNumberOfLines - 1;
			si.nPage = cyClient / cyChar;
			SetScrollInfo(hWnd, SB_VERT, &si, TRUE);

			si.cbSize = sizeof(SCROLLINFO);
			si.fMask = SIF_RANGE | SIF_PAGE;
			si.nMin = 0;
			si.nMax = g_uMaxLength;
			si.nPage = cxClient / cxChar;
			SetScrollInfo(hWnd, SB_HORZ, &si, TRUE);

			break;

		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			
			si.fMask = SIF_POS;
			GetScrollInfo(hWnd, SB_VERT, &si);
			iVertPos = si.nPos;
			
			si.fMask = SIF_POS;
			GetScrollInfo(hWnd, SB_HORZ, &si);
			iHorzPos = si.nPos;

			iPaintBeg = iVertPos + ps.rcPaint.top / cyChar;
			iPaintEnd = iVertPos + ps.rcPaint.bottom / cyChar;
			if(iPaintBeg < 0)
				iPaintBeg = 0;
			if(iPaintEnd >= gpLinesInFiles->uNumberOfLines)
				iPaintEnd = gpLinesInFiles->uNumberOfLines - 1;

			for(i = iPaintBeg; i <= iPaintEnd; ++i)
			{
				x = (1 - iHorzPos) * cxChar;
				y = (i - iVertPos) * cyChar;
				TextOut(	hdc, x, y,
							gpLinesInFiles->pArrayOfStrings[i],
							strlen(gpLinesInFiles->pArrayOfStrings[i])
						);
			}
			EndPaint(hWnd, &ps);
			hdc = NULL;
			break;

		case WM_HSCROLL:
			si.cbSize = sizeof(si);
			si.fMask = SIF_ALL;
			GetScrollInfo(hWnd, SB_HORZ, &si);

			iHorzPos = si.nPos;

			switch(LOWORD(wParam))
			{
				case SB_LINELEFT:
					si.nPos -= 1;
					break;

				case SB_LINERIGHT:
					si.nPos += 1;
					break;

				case SB_PAGELEFT:
					si.nPos -= si.nPage;
					break;

				case SB_PAGERIGHT:
					si.nPos += si.nPage;
					break;

				case SB_THUMBPOSITION:
					si.nPos = si.nTrackPos;
					break;
			}

			si.fMask = SIF_ALL;
			SetScrollInfo(hWnd, SB_HORZ, &si, TRUE);
			GetScrollInfo(hWnd, SB_HORZ, &si);
			if(si.nPos != iHorzPos)
			{
				ScrollWindow(hWnd, cxChar * (iHorzPos - si.nPos), 0, NULL, NULL);
				UpdateWindow(hWnd);
			}
			break;

		case WM_VSCROLL:
			si.cbSize = sizeof(si);
			si.fMask = SIF_ALL;
			GetScrollInfo(hWnd, SB_VERT, &si);

			iVertPos = si.nPos;

			switch(LOWORD(wParam))
			{
				case SB_TOP:
					si.nPos = si.nMin;
					break;

				case SB_BOTTOM:
					si.nPos = si.nMax;
					break;

				case SB_LINEUP:
					si.nPos -= 1;
					break;

				case SB_LINEDOWN:
					si.nPos += 1;
					break;

				case SB_PAGEUP:
					si.nPos -= si.nPage;
					break;

				case SB_PAGEDOWN:
					si.nPos += si.nPage;
					break;

				case SB_THUMBTRACK:
					si.nPos = si.nTrackPos;
					break;
			}

			si.fMask = SIF_ALL;
			SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
			GetScrollInfo(hWnd, SB_VERT, &si);
			if(si.nPos != iVertPos)
			{
				ScrollWindow(hWnd, 0, cyChar * (iVertPos - si.nPos), NULL, NULL);
				UpdateWindow(hWnd);
			}
			break;

		case WM_DESTROY:
			PostQuitMessage(EXIT_SUCCESS);
			break;
	}

	return(DefWindowProc(hWnd, uMsg, wParam, lParam));
}

void ReleaseAll(void)
{
	if(gpLinesInFiles)
	{
		DestroyVectorOfStrings(gpLinesInFiles);
		gpLinesInFiles = NULL;
	}
}

P_VECTOR_OF_STRINGS CreateVectorOfStrings(void)
{
	P_VECTOR_OF_STRINGS pVectorOfStrings = NULL;
	pVectorOfStrings = (P_VECTOR_OF_STRINGS)malloc(sizeof(VECTOR_OF_STRINGS));
	FAIL_EXIT_IF(pVectorOfStrings == NULL, "malloc", "out of virtual address space");
	pVectorOfStrings->pArrayOfStrings = NULL;
	pVectorOfStrings->uNumberOfLines = 0;
	return (pVectorOfStrings);
}

ATOM PushBackInVectorOfStrings(P_VECTOR_OF_STRINGS pVectorOfStrings, CHAR* szString)
{
	pVectorOfStrings->uNumberOfLines += 1;
	pVectorOfStrings->pArrayOfStrings = (CHAR**)realloc(pVectorOfStrings->pArrayOfStrings,
														pVectorOfStrings->uNumberOfLines * sizeof(CHAR*));
	FAIL_EXIT_IF(pVectorOfStrings->pArrayOfStrings == NULL, "realloc", "out of virtual address space");
	pVectorOfStrings->pArrayOfStrings[pVectorOfStrings->uNumberOfLines - 1] = szString;
	return (SUCCESS);
}

ATOM DestroyVectorOfStrings(P_VECTOR_OF_STRINGS pVectorOfStrings)
{
	UINT uCnt;
	for(uCnt = 0; uCnt != pVectorOfStrings->uNumberOfLines; uCnt++)
		free(pVectorOfStrings->pArrayOfStrings[uCnt]);
	free(pVectorOfStrings->pArrayOfStrings);
	free(pVectorOfStrings);
	pVectorOfStrings = NULL;
	return (SUCCESS);
}

P_VECTOR_OF_STRINGS ReadFileInMemory(LPSTR szFileName)
{
	P_VECTOR_OF_STRINGS pLinesInFile = NULL;
	FILE* fp = NULL;
	errno_t err;
	static CHAR szBuffer[BUFFER_SIZE];
	CHAR* pStr = NULL;
	UINT uStringLength;

	pLinesInFile = CreateVectorOfStrings();
	err = fopen_s(&fp, szFileName, "r");
	FAIL_EXIT_IF(err != 0, "fopen_s", "could not open an input file");

	while(fgets(szBuffer, BUFFER_SIZE, fp) != NULL)
	{
		uStringLength = strlen(szBuffer);
		if(uStringLength > g_uMaxLength)
			g_uMaxLength = uStringLength;
		pStr = (CHAR*)malloc(uStringLength + 1);
		FAIL_EXIT_IF(pStr == NULL, "malloc", "out of virtual memory");
		ZeroMemory(pStr, uStringLength + 1);
		strncpy(pStr, szBuffer, uStringLength);
		PushBackInVectorOfStrings(pLinesInFile, pStr);
		ZeroMemory(szBuffer, BUFFER_SIZE);
	}

	fclose(fp);
	fp = NULL;

	return(pLinesInFile);
}