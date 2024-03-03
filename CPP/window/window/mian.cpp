#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
	char window_title[256];
	auto window = FindWindowExA;
	cout << window << endl;

	HWND foreground = GetForegroundWindow();
	if (foreground)
	{
		GetWindowTextA(foreground, window_title, 256);
	}
	cout << foreground << endl;
	cout << window_title << endl;


	return 0;
}