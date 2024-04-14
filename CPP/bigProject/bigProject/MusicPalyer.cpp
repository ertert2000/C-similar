#include <Windows.h>
#include <iostream>
#include <string>
#include <map>
#include "bass.h"
#include "MusicPalyer.h"

#pragma comment (lib, "bass.lib")

typedef std::map < std::string, HSTREAM > MusicMap;
void palyMusic()
{
	int Volume;
	bool flag = true;
	std::string Music_Name;

	std::cout << "enter patch to file" << std::endl;
	std::getline(std::cin, Music_Name);

	std::cout << "enter volume" << std::endl;
	std::cin >> Volume;

	HSTREAM Init = 0;//Stream handle
	MusicMap Music;
	BASS_Init(-1, 44100, 0, 0, 0);
	BASS_SetConfig(BASS_CONFIG_GVOL_STREAM, Volume * 40);

	//Create a new stacker
	MusicMap::iterator _findReturn = Music.find(Music_Name);
	Init = BASS_StreamCreateFile(FALSE, Music_Name.c_str(), 0, 0, BASS_SAMPLE_LOOP);//Get stream handle
	Music.insert(make_pair(Music_Name, Init));//Write to the list
	
	BASS_ChannelPlay(Init, TRUE);//Play

	while (flag)
		if (GetAsyncKeyState(VK_NUMPAD1))
			flag = false;

	for (MusicMap::iterator i = Music.begin(); i != Music.end(); i++)
			BASS_StreamFree(i->second);

	Music.clear();
	BASS_Free();
}