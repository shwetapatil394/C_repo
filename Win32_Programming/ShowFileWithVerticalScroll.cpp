/*
 *	@file:		ShowFileWithVerticalScroll.cpp
 *	@details:	Text reader with vertical scroll bar
 */

#include <Windows.h>
#include <stdio.h>

#include "StringVector.h"

#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "kernel32.lib")

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
PSTRINGVECTOR ReadFileInMemory(LPTSTR lpFileName);
void ReleaseAll(void);

#define FAIL_EXIT_IF(COND, MSG, CAPTION)		do\
												{\
														if((COND) == TRUE)\
														{\
																MessageBox(NULL, TEXT(MSG), TEXT(CAPTION), MB_ICONERROR);\
																ReleaseAll();\
																ExitProcess(EXIT_FAILURE);\
														}\
												} while (0)\


/* Global Handles */
LPSTR glpCmdLine = NULL;
PSTRINGVECTOR gpStrVec = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	static TCHAR szClassName[] = TEXT("The Standard Window");
	static TCHAR szWindowCaption[] = TEXT("Text File Reader");

	HBRUSH hBrush = NULL;
	HCURSOR hCursor = NULL;
	HICON hIcon = NULL;
	HICON hIconSm = NULL;
	HWND hWnd = NULL;
	ATOM bIsWindowClassRegistered = 0;

	WNDCLASSEX wndEx;
	MSG msg;

	glpCmdLine = lpCmdLine;

	ZeroMemory(&wndEx, sizeof(WNDCLASSEX));
	ZeroMemory(&msg, sizeof(MSG));

	hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
	FAIL_EXIT_IF(hBrush == NULL, "Failed to obtain a brush", "GetStockObject");

	hCursor = LoadCursor((HINSTANCE)NULL, IDC_ARROW);
	FAIL_EXIT_IF(hCursor == NULL, "Failed to get cursor", "LoadCursor");

	hIcon = LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);
	FAIL_EXIT_IF(hIcon == NULL, "Failed to load icon", "LoadIcon");

	hIconSm = LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);
	FAIL_EXIT_IF(hIconSm == NULL, "Failed to load small icon", "LoadIcon");

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
	wndEx.style = CS_HREDRAW | CS_VREDRAW;

	bIsWindowClassRegistered = RegisterClassEx(&wndEx);
	FAIL_EXIT_IF(bIsWindowClassRegistered == 0, "Failed to register window class", "RegisterClassEx");

	hWnd = CreateWindowEx(WS_EX_APPWINDOW, szClassName, szWindowCaption, 
							WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU |
							WS_THICKFRAME | WS_VSCROLL,
							CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
							(HWND)NULL, (HMENU)NULL, hInstance, NULL);
	FAIL_EXIT_IF(hWnd == NULL, "Failed to create window", "CreateWindowEx");

	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);

	while(GetMessage(&msg, (HWND)NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	ReleaseAll();
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static int cxChar, cyChar, cxCaps, cyClient, iVScrollPos = 0;
	int iCnt = 0;

	HDC hdc = NULL;
	TEXTMETRIC tm;
	PAINTSTRUCT ps;

	switch(uMsg)
	{
		case WM_CREATE:
			hdc = GetDC(hWnd);
			GetTextMetrics(hdc, &tm);
			cxChar = tm.tmAveCharWidth;
			cyChar = tm.tmHeight + tm.tmExternalLeading;
			cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar / 2;

			ReleaseDC(hWnd, hdc);
			hdc = NULL;

			gpStrVec = ReadFileInMemory(glpCmdLine);
			SetScrollRange(hWnd, SB_VERT, 0, gpStrVec->iVectorSize, FALSE);
			SetScrollPos(hWnd, SB_VERT, iVScrollPos, TRUE);
			break;

		case WM_SIZE:
			cyClient = HIWORD(lParam);
			break;

		case WM_VSCROLL:
			switch(LOWORD(wParam))
			{
				case SB_LINEUP:
					iVScrollPos -= 1;
					break;

				case SB_LINEDOWN:
					iVScrollPos += 1;
					break;

				case SB_PAGEUP:
					iVScrollPos -= cyClient/cyChar;
					break;

				case SB_PAGEDOWN:
					iVScrollPos += cyClient/cyChar;
					break;

				case SB_THUMBPOSITION:
					iVScrollPos = HIWORD(wParam);
					break;

				default:
					break;
			}

			if(iVScrollPos < 0)
				iVScrollPos = 0;
			else if(iVScrollPos > gpStrVec->iVectorSize - 1)
				iVScrollPos = gpStrVec->iVectorSize -1;

			if(iVScrollPos != GetScrollPos(hWnd, SB_VERT))
			{
				SetScrollPos(hWnd, SB_VERT, iVScrollPos, TRUE);
				InvalidateRect(hWnd, NULL, TRUE);
			}
			break;

		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			for(iCnt = 0; iCnt < gpStrVec->iVectorSize; ++iCnt)
			{
				TextOutA(hdc, 0, (iCnt-iVScrollPos)*cyChar, gpStrVec->ppString[iCnt], strlen(gpStrVec->ppString[iCnt]));
			}
			EndPaint(hWnd, &ps);
			hdc = NULL;
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}
	return(DefWindowProc(hWnd, uMsg, wParam, lParam));
}

PSTRINGVECTOR ReadFileInMemory(LPSTR lpFileName)
{
	#define BUFFER_SIZE	128

	FILE* fp = NULL;
	CHAR chBuffer[BUFFER_SIZE];
	PCHAR pStr = NULL;
	int iStrLen;

	fp = fopen(lpFileName, "r");
	FAIL_EXIT_IF(fp == NULL, "Could not open input file", "fopen");

	gpStrVec = CreateStringVector();

	memset(chBuffer, 0, BUFFER_SIZE);
	while(fgets(chBuffer, BUFFER_SIZE, fp) != NULL)
	{
		iStrLen = strnlen_s(chBuffer, BUFFER_SIZE);
		pStr = (PCHAR)Xcalloc(1, iStrLen+1);
		strncpy(pStr, chBuffer, iStrLen);
		PushBack(gpStrVec, pStr);
		memset(chBuffer, 0, BUFFER_SIZE);
	}

	fclose(fp);
	fp = NULL;

	return (gpStrVec);
}

void ReleaseAll(void)
{
	if(gpStrVec != NULL)
	{
		DestroyStringVector(gpStrVec);
		gpStrVec = NULL;
	}
}