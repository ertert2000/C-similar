#include <iostream>
#include <windows.h>


using namespace std;
void clikWindow(HWND window)
{
	SendMessage(HWND_BROADCAST, WM_LBUTTONDOWN, 500, 500);
	SendMessage(HWND_BROADCAST, WM_LBUTTONUP, 500, 500);
}

int main()
{

	while (true)
	{
		int onIn = 0;
		int infinity = 1;1
		int delay, changeDelay;
		bool clik;
		puts("#----------------------------#");
		puts("1 - enable autoclicker");
		puts("2 - exit the program");
		puts("#----------------------------#");
		cin >> onIn;

		system("cls");
		switch (onIn)
		{
		case 1:
			clik = false;
			delay = 5000, changeDelay;

			puts("#----------------------------#");
			puts("change delay| YES - 1| NO - 2");
			puts("Num Pad 1 - launch the clicker");
			puts("Num Pad 2 - stop clicker");
			puts("Num Pad 5 - back to menu");
			puts("#----------------------------#");
			
			cin >> changeDelay;

			if (changeDelay == 1)
			{
				puts("1000 = 1sec| 2500 = 2.5sec| 5000 = 5sec");
				puts("Enter delay");
				cin >> delay;
			}
			
			while (infinity == 1)
			{
				auto GTAWindow = GetForegroundWindow();
				if (GetAsyncKeyState(VK_NUMPAD1))
					clik = true;
				if (GetAsyncKeyState(VK_NUMPAD2))
					clik = false;
				if (GetAsyncKeyState(VK_NUMPAD5))
					infinity = 0;

				if (clik == true)
				{
					clikWindow(GTAWindow);
					Sleep(delay);
				}

			}


			system("cls");
			break;
		case 2:
			return 0;
		}

	}
}