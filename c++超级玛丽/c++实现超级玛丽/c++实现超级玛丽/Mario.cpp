/*未完成的
* ③加速度
*/
#include "Bkground.h"
#include "Mario.h"	
#include "Obstacle.h"
#include "Spirits.h"
#include "Enemies.h"
#include <iostream>

void Mario::change_map()
{
	if (x - Map.x < map_show_left)
		Map.bk_move(x - Map.x - map_show_left);
	else if (x - Map.x > map_show_right)
		Map.bk_move(x - Map.x - map_show_right);
}

void Mario::init()					//初始化人物
{
	state = true;
	is_stand = 1;				//五种状态
	is_walk = 0;	stop_time = 0;	walk_step = 0;
	is_jump = 0;
	is_squat = 0;
	is_death = 0;

	direction = 2;			//左右方向
	vx = 0;		int vx_max = 8;	int ax = 1;		//x方向速度和加速度（摩檫力的）
	vy = 0;		int vy_max = 36;	int ay = 3;		//y方向速度和加速度（摩檫力的）

	length = Mario_Small_Length;
	height = Mario_Small_Height;
	x = 100;
	y = 600 - height;		//600是地图的地面

	buffer = 0;		
	buffer_time = 0;

	is_over = false;
	is_win = false;

	mci_jump_sound = 0;
	mci_jump_times = 0;
	mci_turn_sound = 0;
	mci_turn_times = 0;
	mci_hit_sound = 0;
	mci_hit_times = 0;
	mci_attack_sound = 0;
	mci_attack_times = 0;
	mci_magic_sound = 0;
	mci_magic_times = 0;
	mci_coin_sound = 0;
	mci_coin_times = 0;
	mci_flag_sound = 0;
	mci_flag_times = 0;
	mci_stomp_sound = 0;
	mci_stomp_times = 0;

	load_img();

	Bullet::init();
}

void Mario::load_img()
{
	//正常
	loadimage(&img_dead[0][0], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Mario\\deadjump00.png");		//死亡
	loadimage(&img_dead[0][1], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Mario\\deadjump01.png");

	loadimage(&img_jump[0][0], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Mario\\jumpL00.png");		//跳
	loadimage(&img_jump[0][1], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Mario\\jumpL01.png");
	loadimage(&img_jump[0][2], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Mario\\jumpR00.png");
	loadimage(&img_jump[0][3], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Mario\\jumpR01.png");

	loadimage(&img_walk[0][0], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Mario\\walkL00.png");		//走
	loadimage(&img_walk[0][1], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Mario\\walkL01.png");
	loadimage(&img_walk[0][2], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Mario\\walkR00.png");
	loadimage(&img_walk[0][3], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Mario\\walkR01.png");

	loadimage(&img_stand[0][0], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Mario\\standL00.png");	//站
	loadimage(&img_stand[0][1], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Mario\\standL01.png");
	loadimage(&img_stand[0][2], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Mario\\standR00.png");
	loadimage(&img_stand[0][3], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Mario\\standR01.png");

	//蘑菇（变大）
	loadimage(&img_jump[1][0], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Mario\\jumpLbuff10.png");		//跳
	loadimage(&img_jump[1][1], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Mario\\jumpLbuff11.png");
	loadimage(&img_jump[1][2], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Mario\\jumpRbuff10.png");
	loadimage(&img_jump[1][3], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Mario\\jumpRbuff11.png");

	loadimage(&img_walk[1][0], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Mario\\walkLbuff10.png");		//走
	loadimage(&img_walk[1][1], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Mario\\walkLbuff11.png");
	loadimage(&img_walk[1][2], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Mario\\walkRbuff10.png");
	loadimage(&img_walk[1][3], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Mario\\walkRbuff11.png");

	loadimage(&img_stand[1][0], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Mario\\standLbuff10.png");	//站
	loadimage(&img_stand[1][1], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Mario\\standLbuff11.png");
	loadimage(&img_stand[1][2], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Mario\\standRbuff10.png");
	loadimage(&img_stand[1][3], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Mario\\standRbuff11.png");

	//花朵（厨师子弹）
	loadimage(&img_jump[2][0], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Mario\\jumpLbuff20.png");		//跳
	loadimage(&img_jump[2][1], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Mario\\jumpLbuff21.png");
	loadimage(&img_jump[2][2], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Mario\\jumpRbuff20.png");
	loadimage(&img_jump[2][3], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Mario\\jumpRbuff21.png");

	loadimage(&img_walk[2][0], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Mario\\walkLbuff20.png");		//走
	loadimage(&img_walk[2][1], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Mario\\walkLbuff21.png");
	loadimage(&img_walk[2][2], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Mario\\walkRbuff20.png");
	loadimage(&img_walk[2][3], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Mario\\walkRbuff21.png");

	loadimage(&img_stand[2][0], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Mario\\standLbuff20.png");	//站
	loadimage(&img_stand[2][1], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Mario\\standLbuff21.png");
	loadimage(&img_stand[2][2], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Mario\\standRbuff20.png");
	loadimage(&img_stand[2][3], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Mario\\standRbuff21.png");
}

void Mario::put_img()
{
	Bullet::put_img();

	int x_show = x - Map.x;
	if (x_show < 0) x_show = 0;											//在地图的左边界
	else if (x > 50 && x_show < 50) x_show = map_show_left;					//靠左走（未到达地图左边界）
	else if (x < Map.length - MAP_EXTRA - WD_LENGTH + map_show_right && x_show > map_show_right) x_show = map_show_right;	//靠右走（未到达地图右边界）
	else if (x + length > Map.length - MAP_EXTRA) x_show = Map.length - MAP_EXTRA - length;

	if (!state)			//死亡后动作（一定要写在put_img里面，因为缓冲的原因）
	{
		putimage(x_show, y, length, height, &img_dead[0][0], 0, 0, SRCAND);
		putimage(x_show, y, length, height, &img_dead[0][1], 0, 0, SRCPAINT);
		if (vy == -vdead_max+adead) Sleep(250);
		Sleep(40);
		return;
	}

	if (is_win) return;			//走进门获胜不显示马里奥

	//------------------------------------------------------------ 正常状态 ---------------------------------------------------------
	if (buffer == 0)
	{
		if (is_jump)
		{
			if (direction == 1)
			{
				putimage(x_show, y, length, height, &img_jump[0][0], 0, 0, SRCAND);
				putimage(x_show, y, length, height, &img_jump[0][1], 0, 0, SRCPAINT);
			}
			else if (direction == 2)
			{
				putimage(x_show, y, length, height, &img_jump[0][2], 0, 0, SRCAND);
				putimage(x_show, y, length, height, &img_jump[0][3], 0, 0, SRCPAINT);
			}
		}
		else if (is_walk)
		{
			++stop_time;
			if (direction == 1)
			{
				if (walk_step == 0)
				{
					putimage(x_show, y, length, height, &img_walk[0][0], 64, 0, SRCAND);
					putimage(x_show, y, length, height, &img_walk[0][1], 64, 0, SRCPAINT);
					if (stop_time == 10)
					{
						stop_time = 0;
						walk_step = 1;
					}
				}
				else
				{
					putimage(x_show, y, length, height, &img_walk[0][0], 0, 0, SRCAND);
					putimage(x_show, y, length, height, &img_walk[0][1], 0, 0, SRCPAINT);
					if (stop_time == 10)
					{
						stop_time = 0;
						walk_step = 0;
					}
				}
			}
			else if (direction == 2)
			{
				if (walk_step == 0)
				{
					putimage(x_show, y, length, height, &img_walk[0][2], 64, 0, SRCAND);
					putimage(x_show, y, length, height, &img_walk[0][3], 64, 0, SRCPAINT);
					if (stop_time == 10)
					{
						stop_time = 0;
						walk_step = 1;
					}
				}
				else
				{
					putimage(x_show, y, length, height, &img_walk[0][2], 0, 0, SRCAND);
					putimage(x_show, y, length, height, &img_walk[0][3], 0, 0, SRCPAINT);
					if (stop_time == 10)
					{
						stop_time = 0;
						walk_step = 0;
					}
				}
			}
		}
		else if (is_stand)
		{
			if (direction == 1)
			{
				putimage(x_show, y, length, height, &img_stand[0][0], 0, 0, SRCAND);
				putimage(x_show, y, length, height, &img_stand[0][1], 0, 0, SRCPAINT);
			}
			else if (direction == 2)
			{
				putimage(x_show, y, length, height, &img_stand[0][2], 0, 0, SRCAND);
				putimage(x_show, y, length, height, &img_stand[0][3], 0, 0, SRCPAINT);
			}
		}
	}
	
	//------------------------------------------------------------ 状态1：变大 ---------------------------------------------------------
	else if (buffer == 1)
	{
		if (is_jump)
		{
			if (direction == 1)
			{
				putimage(x_show, y, length, height, &img_jump[1][0], 0, 0, SRCAND);
				putimage(x_show, y, length, height, &img_jump[1][1], 0, 0, SRCPAINT);
			}
			else if (direction == 2)
			{
				putimage(x_show, y, length, height, &img_jump[1][2], 0, 0, SRCAND);
				putimage(x_show, y, length, height, &img_jump[1][3], 0, 0, SRCPAINT);
			}
		}
		else if (is_walk)
		{
			++stop_time;
			if (direction == 1)
			{
				if (walk_step == 0)
				{
					putimage(x_show, y, length, height, &img_walk[1][0], 0, 0, SRCAND);
					putimage(x_show, y, length, height, &img_walk[1][1], 0, 0, SRCPAINT);
					if (stop_time == 10)
					{
						stop_time = 0;
						walk_step = 1;
					}
				}
				else if(walk_step == 1)
				{
					putimage(x_show, y, length, height, &img_walk[1][0], 64, 0, SRCAND);
					putimage(x_show, y, length, height, &img_walk[1][1], 64, 0, SRCPAINT);
					if (stop_time == 10)
					{
						stop_time = 0;
						walk_step = 2;
					}
				}
				else
				{
					putimage(x_show, y, length, height, &img_walk[1][0], 128, 0, SRCAND);
					putimage(x_show, y, length, height, &img_walk[1][1], 128, 0, SRCPAINT);
					if (stop_time == 10)
					{
						stop_time = 0;
						walk_step = 0;
					}
				}
			}
			else if (direction == 2)
			{
				if (walk_step == 0)
				{
					putimage(x_show, y, length, height, &img_walk[1][2], 0, 0, SRCAND);
					putimage(x_show, y, length, height, &img_walk[1][3], 0, 0, SRCPAINT);
					if (stop_time == 10)
					{
						stop_time = 0;
						walk_step = 1;
					}
				}
				else if(walk_step == 1)
				{
					putimage(x_show, y, length, height, &img_walk[1][2], 64, 0, SRCAND);
					putimage(x_show, y, length, height, &img_walk[1][3], 64, 0, SRCPAINT);
					if (stop_time == 10)
					{
						stop_time = 0;
						walk_step = 2;
					}
				}
				else
				{
					putimage(x_show, y, length, height, &img_walk[1][2], 128, 0, SRCAND);
					putimage(x_show, y, length, height, &img_walk[1][3], 128, 0, SRCPAINT);
					if (stop_time == 10)
					{
						stop_time = 0;
						walk_step = 0;
					}
				}
			}
		}
		else if (is_stand)
		{
			if (direction == 1)
			{
				putimage(x_show, y, length, height, &img_stand[1][0], 0, 0, SRCAND);
				putimage(x_show, y, length, height, &img_stand[1][1], 0, 0, SRCPAINT);
			}
			else if (direction == 2)
			{
				putimage(x_show, y, length, height, &img_stand[1][2], 0, 0, SRCAND);
				putimage(x_show, y, length, height, &img_stand[1][3], 0, 0, SRCPAINT);
			}
		}
	}

	//------------------------------------------------------------ 状态2：无敌 ---------------------------------------------------------
	else if (buffer == 2)
	{
		++flash_time;
		if (flash_time <= 2) { }		//不出现
		else							//出现
		{
			if (flash_time == 4)
				flash_time = 0;
			if (is_jump)
			{
				if (direction == 1)
				{
					putimage(x_show, y, length, height, &img_jump[0][0], 0, 0, SRCAND);
					putimage(x_show, y, length, height, &img_jump[0][1], 0, 0, SRCPAINT);
				}
				else if (direction == 2)
				{
					putimage(x_show, y, length, height, &img_jump[0][2], 0, 0, SRCAND);
					putimage(x_show, y, length, height, &img_jump[0][3], 0, 0, SRCPAINT);
				}
			}
			else if (is_walk)
			{
				++stop_time;
				if (direction == 1)
				{
					if (walk_step == 0)
					{
						putimage(x_show, y, length, height, &img_walk[0][0], 64, 0, SRCAND);
						putimage(x_show, y, length, height, &img_walk[0][1], 64, 0, SRCPAINT);
						if (stop_time == 10)
						{
							stop_time = 0;
							walk_step = 1;
						}
					}
					else
					{
						putimage(x_show, y, length, height, &img_walk[0][0], 0, 0, SRCAND);
						putimage(x_show, y, length, height, &img_walk[0][1], 0, 0, SRCPAINT);
						if (stop_time == 10)
						{
							stop_time = 0;
							walk_step = 0;
						}
					}
				}
				else if (direction == 2)
				{
					if (walk_step == 0)
					{
						putimage(x_show, y, length, height, &img_walk[0][2], 64, 0, SRCAND);
						putimage(x_show, y, length, height, &img_walk[0][3], 64, 0, SRCPAINT);
						if (stop_time == 10)
						{
							stop_time = 0;
							walk_step = 1;
						}
					}
					else
					{
						putimage(x_show, y, length, height, &img_walk[0][2], 0, 0, SRCAND);
						putimage(x_show, y, length, height, &img_walk[0][3], 0, 0, SRCPAINT);
						if (stop_time == 10)
						{
							stop_time = 0;
							walk_step = 0;
						}
					}
				}
			}
			else if (is_stand)
			{
				if (direction == 1)
				{
					putimage(x_show, y, length, height, &img_stand[0][0], 0, 0, SRCAND);
					putimage(x_show, y, length, height, &img_stand[0][1], 0, 0, SRCPAINT);
				}
				else if (direction == 2)
				{
					putimage(x_show, y, length, height, &img_stand[0][2], 0, 0, SRCAND);
					putimage(x_show, y, length, height, &img_stand[0][3], 0, 0, SRCPAINT);
				}
			}
		}
	}

	//------------------------------------------------------------ 状态3：厨师 ---------------------------------------------------------
	else if (buffer == 3)
	{
		if (is_jump)
		{
			if (direction == 1)
			{
				putimage(x_show, y, length, height, &img_jump[2][0], 0, 0, SRCAND);
				putimage(x_show, y, length, height, &img_jump[2][1], 0, 0, SRCPAINT);
			}
			else if (direction == 2)
			{
				putimage(x_show, y, length, height, &img_jump[2][2], 0, 0, SRCAND);
				putimage(x_show, y, length, height, &img_jump[2][3], 0, 0, SRCPAINT);
			}
		}
		else if (is_walk)
		{
			++stop_time;
			if (direction == 1)
			{
				if (walk_step == 0)
				{
					putimage(x_show, y, length, height, &img_walk[2][0], 0, 0, SRCAND);
					putimage(x_show, y, length, height, &img_walk[2][1], 0, 0, SRCPAINT);
					if (stop_time == 10)
					{
						stop_time = 0;
						walk_step = 1;
					}
				}
				else if(walk_step == 1)
				{
					putimage(x_show, y, length, height, &img_walk[2][0], 64, 0, SRCAND);
					putimage(x_show, y, length, height, &img_walk[2][1], 64, 0, SRCPAINT);
					if (stop_time == 10)
					{
						stop_time = 0;
						walk_step = 2;
					}
				}
				else
				{
					putimage(x_show, y, length, height, &img_walk[2][0], 128, 0, SRCAND);
					putimage(x_show, y, length, height, &img_walk[2][1], 128, 0, SRCPAINT);
					if (stop_time == 10)
					{
						stop_time = 0;
						walk_step = 0;
					}
				}
			}
			else if (direction == 2)
			{
				if (walk_step == 0)
				{
					putimage(x_show, y, length, height, &img_walk[2][2], 64, 0, SRCAND);
					putimage(x_show, y, length, height, &img_walk[2][3], 64, 0, SRCPAINT);
					if (stop_time == 10)
					{
						stop_time = 0;
						walk_step = 1;
					}
				}
				else if(walk_step == 1)
				{
					putimage(x_show, y, length, height, &img_walk[2][2], 0, 0, SRCAND);
					putimage(x_show, y, length, height, &img_walk[2][3], 0, 0, SRCPAINT);
					if (stop_time == 10)
					{
						stop_time = 0;
						walk_step = 2;
					}
				}
				else
				{
					putimage(x_show, y, length, height, &img_walk[2][2], 0, 0, SRCAND);
					putimage(x_show, y, length, height, &img_walk[2][3], 0, 0, SRCPAINT);
					if (stop_time == 10)
					{
						stop_time = 0;
						walk_step = 0;
					}
				}
			}
		}
		else if (is_stand)
		{
			if (direction == 1)
			{
				putimage(x_show, y, length, height, &img_stand[2][0], 0, 0, SRCAND);
				putimage(x_show, y, length, height, &img_stand[2][1], 0, 0, SRCPAINT);
			}
			else if (direction == 2)
			{
				putimage(x_show, y, length, height, &img_stand[2][2], 0, 0, SRCAND);
				putimage(x_show, y, length, height, &img_stand[2][3], 0, 0, SRCPAINT);
			}
		}
	}
}

void Mario::music_update()
{
	//拾取金币时候的音乐播放；
	if (mci_coin_sound > 0)
	{
		if (mci_coin_times == 2)
		{
			mciSendString("close coin", NULL, 0, NULL);
			mci_coin_times = 1;
		}
		mciSendString("open E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\music\\coin.mp3 alias coin", NULL, 0, NULL);
		mciSendString("play coin repeat", NULL, 0, NULL);
		mci_coin_sound--;
	}
	else if (mci_coin_sound == 0)
	{
		mciSendString("close coin", NULL, 0, NULL);
		mci_coin_sound = 0;
		mci_coin_times = 0;

	}

	//变身时候的音乐播放；
	if (mci_turn_sound > 0)
	{
		if (mci_turn_times == 2)
		{
			mciSendString("close turn", NULL, 0, NULL);
			mci_turn_times = 1;
		}
		mciSendString("open E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\music\\powerup.mp3 alias turn", NULL, 0, NULL);
		mciSendString("play turn repeat", NULL, 0, NULL);
		mci_turn_sound--;
	}
	else if (mci_turn_sound == 0)
	{
		mciSendString("close turn", NULL, 0, NULL);
		mci_turn_sound = 0;
		mci_turn_times = 0;
	}

	//跳跃时候的音乐播放；
	if (mci_jump_sound > 0)
	{
		if (mci_jump_times == 2)
		{
			mciSendString("close jump", NULL, 0, NULL);
			mci_jump_times = 1;
		}
		mciSendString("open E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\music\\small_jump.mp3 alias jump", NULL, 0, NULL);
		mciSendString("play jump repeat", NULL, 0, NULL);
		mci_jump_sound--;
	}
	else if (mci_jump_sound == 0)
	{
		mciSendString("close jump", NULL, 0, NULL);
		mci_jump_sound = 0;
		mci_jump_times = 0;
	}

	//撞击砖块时候的音乐播放；
	if (mci_hit_sound > 0)
	{
		if (mci_hit_times == 2)
		{
			mciSendString("close hit", NULL, 0, NULL);
			mci_hit_times = 1;
		}
		mciSendString("open E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\music\\bump.mp3 alias hit", NULL, 0, NULL);
		mciSendString("play hit repeat", NULL, 0, NULL);
		mci_hit_sound--;
	}
	else if (mci_hit_sound == 0)
	{
		mciSendString("close hit", NULL, 0, NULL);
		mci_hit_sound = 0;
		mci_hit_times = 0;
	}

	//发射火焰弹时候的音乐播放；
	if (mci_attack_sound > 0)
	{
		if (mci_attack_times == 2)
		{
			mciSendString("close fire", NULL, 0, NULL);
			mci_attack_times = 1;
		}
		mciSendString("open E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\music\\fireball.mp3 alias fire", NULL, 0, NULL);
		mciSendString("play fire repeat", NULL, 0, NULL);
		mci_attack_sound--;
	}
	else if (mci_attack_sound == 0)
	{
		mciSendString("close fire", NULL, 0, NULL);
		mci_attack_sound = 0;
		mci_attack_times = 0;
	}

	//撞击砖块时候的音乐播放；
	if (mci_magic_sound > 0)
	{
		if (mci_magic_times == 2)
		{
			mciSendString("close magic", NULL, 0, NULL);
			mci_magic_times = 1;
		}
		mciSendString("open E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\music\\one_up.mp3 alias magic", NULL, 0, NULL);
		mciSendString("play magic repeat", NULL, 0, NULL);
		mci_magic_sound--;
	}
	else if (mci_magic_sound == 0)
	{
		mciSendString("close magic", NULL, 0, NULL);
		mci_magic_sound = 0;
		mci_magic_times = 0;
	}

	//杀死敌人时的音乐播放；
	if (mci_stomp_sound > 0)
	{
		if (mci_stomp_times == 2)
		{
			mciSendString("close stomp", NULL, 0, NULL);
			mci_stomp_times = 1;
		}
		mciSendString("open E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\music\\stomp.mp3 alias stomp", NULL, 0, NULL);
		mciSendString("play stomp repeat", NULL, 0, NULL);
		mci_stomp_sound--;
	}
	else if (mci_stomp_sound == 0)
	{
		mciSendString("close stomp", NULL, 0, NULL);
		mci_stomp_sound = 0;
		mci_stomp_times = 0;
	}
}

void Mario::up_date()
{
	Bullet::up_date();
	//-------------------------------------------------------------
	if (!state)	//如果死亡就执行死亡操作
	{
		dead_manip();
		return;
	}

	if (Flag::is_touch(*this))
	{
		return;
	}

	if (is_win) return;

	y += vy;	//先加上y，再检测（注意，此处不能把x也一起写了，只能先判断往上是否有问题，否则加了x会出bug
	//-------------------------------------------------------- 上面碰撞的检测 
	int up_pos;
	bool up_check = Spe_Brick::is_collide_up(*this, up_pos) || Com_Brick::is_collide_up(*this, up_pos);
	if (is_jump && vy <= 0 && up_check)
	{
		vy = ay;
		y = up_pos;
		mci_hit_sound = 40;
		++mci_hit_times;
	}

	//-------------------------------------------------------- 底面碰撞的检测 
	int down_pos;
	bool down_check = Obstacle::is_collide_down(*this, down_pos) || Com_Brick::is_collide_down(*this, down_pos) || Spe_Brick::is_collide_down(*this, down_pos);		//先检测下方是否有碰撞
	if (is_jump)
	{
		vy += ay;
		if (vy >= 0 && down_check)		//向下运动时发生了碰撞
		{
			vy = 0;
			is_jump = 0;
			y = down_pos - height;
		}
	}
	if (!is_jump && !down_check)	//下方没东西时自动掉落
	{
		is_jump = 1;
		vy += ay;
	}

	//-------------------------------------------------------- 左右碰撞的检测 
	x += vx;
	if (is_walk)
	{
		if (direction == 1)				//左边碰撞
		{
			vx += ax;
			int left_pos;
			bool left_check = Obstacle::is_collide_left(*this, left_pos) || Com_Brick::is_collide_left(*this, left_pos) || Spe_Brick::is_collide_left(*this, left_pos);
			if (vx < 0 && left_check)
			{
				vx = 0;
				is_walk = 0;
				x = left_pos;
			}
		}
		else if (direction == 2)
		{
			vx -= ax;
			int right_pos;
			bool right_check = Obstacle::is_collide_right(*this, right_pos) || Com_Brick::is_collide_right(*this, right_pos) || Spe_Brick::is_collide_right(*this, right_pos);
			if (vx > 0 && right_check)
			{
				vx = 0;
				is_walk = 0;
				x = right_pos - length;
			}
		}
	}
	if (vx == 0) is_walk = 0;

	//-------------------------------------------------------- 下蹲的检测 
	if (is_squat) is_squat = 0;

	//------------------------------------------------------------检测是否碰到敌人
	bool trample = false;
	bool is_attack = buffer == 2 ? true : false;
	if (Goomba::touch(*this, trample, is_attack) || Tortoise::touch(*this, trample, is_attack) || Piranha::touch(*this, trample, is_attack))
	{
		if (trample)
		{
			Mali.is_jump = 1;
			Mali.vy = -Mali.vy_max;
		}
		else
		{
			switch (buffer)
			{
			case 0:
				state = false;
				break;
			case 1:			//变回原样（有一小段无敌时间，变小）
			case 3:
				buffer_time = buffer_alltime * 4 / 5;
				buffer = 2;
				y += Mario_Big_Height - Mario_Small_Height;
				height = Mario_Small_Height;
				break;
			default:
				break;
			}
		}
		if (state)
		{
			mci_stomp_sound = 30;
			++mci_stomp_times;
		}
	}

	//------------------------------------------------------------状态的时间
	Spe_Brick::eat(Mali);
	Coin::eat(Mali);
	if ((buffer == 1 || buffer == 3) && buffer_time >= buffer_alltime * 19 / 20)
	{
		buffer = 2;
		y += Mario_Big_Height - Mario_Small_Height;
		height = Mario_Small_Height;
	}
	if (buffer != 0)
	{
		++buffer_time;
		if (buffer_time >= buffer_alltime)
		{
			if (Mali.height == Mario_Big_Height)
			{
				Mali.y += Mario_Big_Height - Mario_Small_Height;
				Mali.height = Mario_Small_Height;
			}
			buffer_time = 0;
			buffer = 0;
		}
	}

	if (y > 2 * WD_HEIGHT) state = false;

	change_map();

	if (x >= 9770 && y == MAP_LAND - height) is_win = true;

	if (!state)		//死亡后第一次动作（后面不会再进入）
	{
		Mali.vy = -Mali.vdead_max;
	}

	music_update();
}

void Mario::clear_manip()		//调用初始化函数恢复到最初
{
	Bullet::clear_manip();

	init();
}

void Mario::dead_manip()
{
	mciSendString("close coin", 0, 0, 0);
	mciSendString("close turn", 0, 0, 0);
	mciSendString("close jump", 0, 0, 0);
	mciSendString("close hit", 0, 0, 0);
	mciSendString("close fire", 0, 0, 0);
	mciSendString("close magic", 0, 0, 0);
	mciSendString("close stomp", 0, 0, 0);

	y += vy;
	vy += adead;
	if (y > 3000)
	{
		is_over = true;
	}
}






//-------------------------------------------------------------------- 子弹 ----------------------------------------------------------------------
IMAGE bullet_img[2];
int Bullet::num = 0;
Bullet Bl[Bullet::all_num];

void Bullet::load_img()
{
	loadimage(&bullet_img[0], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Mario\\bullet0.png");
	loadimage(&bullet_img[1], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Mario\\bullet1.png");
}

void Bullet::init()
{
	for (int i = 0; i < Bullet::all_num; ++i)
	{
		Bullet::num = 0;
		Bl[i].length = Bullet_Length;
		Bl[i].height = Bullet_Height;
		Bl[i].state = false;
		Bl[i].vx = 0;
		Bl[i].vy = 0;
	}

	load_img();
}

void Bullet::put_img()
{
	for (int i = 0; i < Bullet::all_num; ++i)
	{
		if (!Bl[i].state) continue;
		putimage(Bl[i].x - Map.x, Bl[i].y, Bl[i].length, Bl[i].height, &bullet_img[0], 0, 48, SRCAND);		//6,6是图片位置（小子弹所在位置）
		putimage(Bl[i].x - Map.x, Bl[i].y, Bl[i].length, Bl[i].height, &bullet_img[1], 0, 48, SRCPAINT);
	}
}

void Bullet::up_date()
{
	for (int i = 0; i < all_num; ++i)
	{
		if (!Bl[i].state) continue;

		Bl[i].y += Bl[i].vy;
		//-------------------------------------------------------- 上面碰撞的检测 -----------------------------------------------------------------------------
		int up_pos;
		bool up_check = Spe_Brick::is_collide_up(Bl[i], up_pos) || Com_Brick::is_collide_up(Bl[i], up_pos);
		if (Bl[i].vy <= 0 && up_check)
		{
			Bl[i].vy = Bl[i].ay;
			Bl[i].y = up_pos;
		}

		//-------------------------------------------------------- 下面碰撞的检测 -----------------------------------------------------------------------------
		int down_pos;
		bool down_check = Obstacle::is_collide_down(Bl[i], down_pos) || Com_Brick::is_collide_down(Bl[i], down_pos) || Spe_Brick::is_collide_down(Bl[i], down_pos);		//先检测下方是否有碰撞
		Bl[i].vy += Bl[i].ay;
		if (Bl[i].vy >= 0 && down_check)		//向下运动时发生了碰撞
		{
			Bl[i].vy = -Bl[i].vy_max;
			Bl[i].y = down_pos - Bl[i].height;
		}

		//-------------------------------------------------------- 左右碰撞的检测（子弹消失）-----------------------------------------------------------------------------
		Bl[i].x += Bl[i].vx;
		//与敌人的碰撞
		bool trample = false;
		if (Goomba::touch(Bl[i], trample, true) || Tortoise::touch(Bl[i], trample, true) || Piranha::touch(Bl[i], trample, true))
		{
			--Bullet::num;
			Bl[i].state = false;
		}

		if (Bl[i].direction == 1)				//左边碰撞
		{
			int left_pos;
			bool left_check = Obstacle::is_collide_left(Bl[i], left_pos) || Com_Brick::is_collide_left(Bl[i], left_pos) || Spe_Brick::is_collide_left(Bl[i], left_pos);
			if (Bl[i].vx < 0 && left_check)
			{
				--Bullet::num;
				Bl[i].state = false;
			}
		}
		else if (Bl[i].direction == 2)			//右边碰撞
		{
			int right_pos;
			bool right_check = Obstacle::is_collide_right(Bl[i], right_pos) || Com_Brick::is_collide_right(Bl[i], right_pos) || Spe_Brick::is_collide_right(Bl[i], right_pos);
			if (Bl[i].vx > 0 && right_check)
			{
				--Bullet::num;
				Bl[i].state = false;
			}
		}
	}
}

void Bullet::clear_manip()
{
	Bullet::init();
}

Mario Mali;