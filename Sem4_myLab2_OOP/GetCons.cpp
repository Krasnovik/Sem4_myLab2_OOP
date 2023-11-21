#pragma once
#include <windows.h>
#include"Classes.h" //объ€вление классов



HWND GetConcolWindow()
{


	char str[128];
	LPWSTR title = (LPWSTR)"xxxxxxxxxxxxxxxxxx";

	GetConsoleTitle((LPWSTR)str, sizeof((LPWSTR)str));

	SetConsoleTitle(title);

	Sleep(100);

	HWND hwnd = FindWindow(NULL, (LPWSTR)title);

	SetConsoleTitle((LPWSTR)str);

	return hwnd;
}