#include <iostream>
#include <graphics.h>
#include <conio.h>
#pragma comment(lib, "winmm.lib")	//加载静态库

#include "Game.h"

int main()
{
	Game gg;
	gg.start_game();
	gg.play_game();

	return 0;
}

