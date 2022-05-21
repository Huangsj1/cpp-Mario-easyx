#include "Game.h"
#include "Bkground.h"
#include "Obstacle.h"
#include "Mario.h"
#include "KeyMsg.h"
#include "Spirits.h"
#include "Enemies.h"
#include <iostream>
#include <mmsystem.h>	//包含多媒体设备接口头文件


IMAGE start_img;
IMAGE pause_img;
IMAGE over_img;

//清除数据
void Game::clear_data()
{
	Map.clear_manip();
	Mali.clear_manip();

	Spe_Brick::clear_manip();
	Coin::clear_manip();
	Flag::clear_manip();
	Goomba::clear_manip();
	Tortoise::clear_manip();
	Piranha::clear_manip();
}

//开始，暂停，结束都要有输出图片
void Game::start_game()
{
	//初始化
	mciSendString("open E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\music\\main_theme.mp3 alias bgm", 0, 0, 0);
	mciSendString("play bgm repeat", 0, 0, 0);
	player = 1;
	score = 0;
	initgraph(WD_LENGTH, WD_HEIGHT, SHOWCONSOLE);

	loadimage(&start_img, "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\BkGround\\start.png");
	loadimage(&pause_img, "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\BkGround\\pause.png");
	loadimage(&over_img, "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\BkGround\\gameover.png");
	Map.load_img();
	Goomba::load_img();
	Tortoise::load_img();
	Piranha::load_img();
	Mali.init();
	Com_Brick::init();
	Spe_Brick::init();
	Coin::init();
	Flag::init();

	putimage(0, 0, WD_LENGTH, WD_HEIGHT,&start_img, 0, 0);
	//游戏开始
	if (is_start())
		start = true;
}

void Game::play_game()
{
	if (start != 1) return;

	BeginBatchDraw();
	while (1)
	{
		if (pause) continue_game();		//游戏暂停
		if (over) 						//游戏结束
		{
			game_over();
			continue;
		}
		if (Mali.is_win)
		{
			game_win();
			continue;
		}

		//图片放置
		cleardevice();
		Map.put_img();
		Mali.put_img();
		Com_Brick::put_img();
		Spe_Brick::put_img();
		Coin::put_img();
		Flag::put_img();
		Goomba::put_img();
		Tortoise::put_img();
		Piranha::put_img();

		FlushBatchDraw();

		//更新状态
		read_msg(*this, Mali);
		Mali.up_date();
		Goomba::up_date();
		Tortoise::up_date();
		Piranha::up_date();

		if (Mali.is_over) over = true;
	}
}

void Game::continue_game()		//游戏处于暂停状态
{
	mciSendString("pause bgm", 0, 0, 0);
	putimage(0, 0, WD_LENGTH, WD_HEIGHT, &pause_img, 0, 0);
	FlushBatchDraw();

	if (is_continue())
	{
		pause = false;
		mciSendString("resume bgm", 0, 0, 0);
	}
}

void Game::game_over()
{
	mciSendString("close bgm", 0, 0, 0);
	putimage(0, 0, WD_LENGTH, WD_HEIGHT, &over_img, 0, 0);
	FlushBatchDraw();
	clear_data();
	Sleep(3000);

	//游戏开始
	putimage(0, 0, WD_LENGTH, WD_HEIGHT, &start_img, 0, 0);
	FlushBatchDraw();
	start = false;
	pause = false;
	over = false;
	if (is_start())
	{
		start = true;
		mciSendString("open E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\music\\main_theme.mp3 alias bgm", 0, 0, 0);
		mciSendString("play bgm repeat", 0, 0, 0);
	}
}


void Game::game_win()
{
	mciSendString("close coin", 0, 0, 0);
	mciSendString("close turn", 0, 0, 0);
	mciSendString("close jump", 0, 0, 0);
	mciSendString("close hit", 0, 0, 0);
	mciSendString("close fire", 0, 0, 0);
	mciSendString("close magic", 0, 0, 0);
	mciSendString("close stomp", 0, 0, 0);
	mciSendString("close bgm", 0, 0, 0);
	int x_show = Mali.length;
	Mali.vx = 8;
	while (x_show >= 0)
	{
		cleardevice();
		Map.put_img();
		Mali.put_img();
		Com_Brick::put_img();
		Spe_Brick::put_img();
		Coin::put_img();
		Flag::put_img();
		Goomba::put_img();
		Tortoise::put_img();
		Piranha::put_img();
		if (x_show > Mali.length / 2)
		{
			putimage(Mali.x - Map.x, Mali.y, x_show, Mali.height, &Mali.img_walk[0][2], 0, 0, SRCAND);
			putimage(Mali.x - Map.x, Mali.y, x_show, Mali.height, &Mali.img_walk[0][3], 0, 0, SRCPAINT);
		}
		else
		{
			putimage(Mali.x - Map.x, Mali.y, x_show, Mali.height, &Mali.img_walk[0][2], 64, 0, SRCAND);
			putimage(Mali.x - Map.x, Mali.y, x_show, Mali.height, &Mali.img_walk[0][3], 64, 0, SRCPAINT);
		}
		FlushBatchDraw();

		Mali.x += Mali.vx;
		x_show -= Mali.vx;

		Sleep(100);
	}
	Sleep(1000);
	clear_data();

	//游戏开始
	putimage(0, 0, WD_LENGTH, WD_HEIGHT, &start_img, 0, 0);
	FlushBatchDraw();
	start = false;
	pause = false;
	over = false;
	if (is_start())
	{
		start = true;
		mciSendString("open E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\music\\main_theme.mp3 alias bgm", 0, 0, 0);
		mciSendString("play bgm repeat", 0, 0, 0);
	}
}