#include <Windows.h>
#include <iostream>
#include <string>
#include "bass.h"
#include "MusicPalyer.h"

//PlaySound(TEXT("C:\\Users\\Иван\\Downloads\\Deustschland.wav"), NULL, SND_FILENAME | SND_SYNC);

#pragma comment (lib, "bass.lib")

class headBoard
{
public:
	headBoard();
	~headBoard();

private:

};

headBoard::headBoard()
{
}

headBoard::~headBoard()
{
}

int main()
{
	palyMusic();
	return 0;
}