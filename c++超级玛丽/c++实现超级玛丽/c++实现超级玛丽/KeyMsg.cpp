//最后要调节sleep

#include "KeyMsg.h"
#include "Game.h"
#include <iostream>
#include <conio.h>		//_kbhit


bool is_start()
{
	char input;
	while (input = _getch())
	{
		if (input == ' ')
			return true;
	}
	return false;
}


bool is_continue()
{
	char input;
	while (input = _getch())
	{
		if (input == 'p' || input == 'P')
			return true;
	}
	return false;
}


void read_msg(Game& gg, Mario& Mali)
{
	if (!Mali.state) return;			//死亡后不可动

	int af = 2 * Mali.ax;	//满足vx_max是ax的倍数，af是ax的倍数
	if (GetAsyncKeyState(VK_UP))		//跳跃
	{
		if (!Mali.is_jump)
		{
			++Mali.mci_jump_times;
			Mali.mci_jump_sound = 30;
			Mali.is_jump = 1;
			Mali.vy = -Mali.vy_max;
		}
	}
	if (GetAsyncKeyState(VK_DOWN))		//下蹲
	{
		if (!Mali.is_jump)
		{
			Mali.is_squat = 1;
		}
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		Mali.direction = 1;		//方向变化

		if (Mali.vx > -Mali.vx_max)		//速度向左
			Mali.vx -= af;
		if (Mali.vx != 0)
		{
			Mali.is_walk = 1;
			if (Mali.vx < 0) Mali.direction = 1;		//判断速度方向
			else if (Mali.vx > 0) Mali.direction = 2;
		}
		else Mali.is_walk = 0;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		Mali.direction = 2;		//方向变化

		if(Mali.vx < Mali.vx_max)		
			Mali.vx += af;
		if (Mali.vx != 0)
		{
			Mali.is_walk = 1;
			if (Mali.vx < 0) Mali.direction = 1;		//判断速度方向
			else if (Mali.vx > 0) Mali.direction = 2;
		}
		else Mali.is_walk = 0;
	}

	//厨师按下空格发射子弹
	if (_kbhit())			//如果有键盘输入就进入此处，没有就继续后面的
	{
		char input = _getch();	
		if (input == 'p' || input == 'P')
		{
			gg.pause = true;
			return;
		}
		if (Mali.buffer == 3 && input == ' ' && Bullet::num < Bullet::all_num)		//还可以发射子弹
		{
			++Bullet::num;
			for (int i = 0; i < Bullet::all_num; ++i)
			{
				if (!Bl[i].state)
				{
					Bl[i].state = true;
					Bl[i].x = Mali.x + Mali.length;
					Bl[i].y = Mali.y + Mali.height / 2;
					Bl[i].direction = Mali.direction;
					Bl[i].vx = Bl[i].direction == 1 ? -Bl[i].vx_max : Bl[i].vx_max;
					Bl[i].vy = 0;
					Mali.mci_attack_sound = 15;
					++Mali.mci_attack_times;

					break;
				}
			}
		}
	}


	Sleep(15);
}