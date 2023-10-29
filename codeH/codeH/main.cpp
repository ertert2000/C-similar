//#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <mmsystem.h>//sndPlaySound

#pragma comment(lib, "winmm.lib")

int main()
{
    wchar_t nyTb[] = L"Dajjte_tank_ - _Malenkijj_64714984.wav";// TAM, rDE "*.exe"
    PlaySound(nyTb, NULL, SND_FILENAME);
    getchar();
    PlaySoundA("C:\\Dajjte_tank_ - _Malenkijj_64714984.wav", NULL, SND_FILENAME);
    getchar();
    PlaySound(L"C:\\Dajjte_tank_ - _Malenkijj_64714984.wav", NULL, SND_FILENAME);
    // HE PA5OTAET
    //mciSendString(nyTb,NULL,0,NULL);
    //PlaySoundW("c:\\ding.wav", NULL, SND_FILENAME);
    //mciSendStringA("c:\\ding.wav" ,NULL,0,NULL);

    return 0;
}