#include "Enemies.h"
#include "Bkground.h"
#include "Obstacle.h"
#include "Spirits.h"
#include <iostream>

IMAGE Gb_img[4][2];		//左，右，死亡（变矮，反转）
IMAGE Tt_img[4][4];		//左，右，龟壳（左右有四张），死亡（乌龟左右旋转）
IMAGE Ph_img[2][4];		//上（四张），下（死亡倒过来）

//------------------------------------------------------------------------ Goomba ---------------------------------------------------------------------
Goomba Gb[Goomba::all_num] =
{
	//{x, y, length, height, state, xl, xr, vx}
	{ 800, MAP_LAND - Goomba_Length, Goomba_Length, Goomba_Length, true, 500, 1000},
	{1000, MAP_LAND - Goomba_Length, Goomba_Length, Goomba_Length, true, 900, 1400},
	{2000, MAP_LAND - Goomba_Length, Goomba_Length, Goomba_Length, true, 1900, 2300},
	{2850, MAP_LAND - Goomba_Length, Goomba_Length, Goomba_Length, true, 2800, 3300},
	{3500, MAP_LAND - Goomba_Length, Goomba_Length, Goomba_Length, true, 3300, 4100},
	{6200, MAP_LAND - Goomba_Length, Goomba_Length, Goomba_Length, true, 4100, 5280},
	{4800, MAP_LAND - Goomba_Length, Goomba_Length, Goomba_Length, true, 4300, 5500},
	{5750, MAP_LAND - Goomba_Length, Goomba_Length, Goomba_Length, true, 5700, 6200},
	{6050, MAP_LAND - Goomba_Length, Goomba_Length, Goomba_Length, true, 6000, 6600},
	{8000, MAP_LAND - Goomba_Length, Goomba_Length, Goomba_Length, true, 7900, 8600},
	{8200, MAP_LAND - Goomba_Length, Goomba_Length, Goomba_Length, true, 8100, 8600},
};

void Goomba::load_img()
{
	loadimage(&Gb_img[0][0], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Enemies\\Goomba\\goombaL00.png");
	loadimage(&Gb_img[0][1], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Enemies\\Goomba\\goombaL01.png");

	loadimage(&Gb_img[1][0], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Enemies\\Goomba\\goombaR00.png");
	loadimage(&Gb_img[1][1], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Enemies\\Goomba\\goombaR01.png");

	loadimage(&Gb_img[2][0], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Enemies\\Goomba\\goombaD0.png");
	loadimage(&Gb_img[2][1], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Enemies\\Goomba\\goombaD1.png");
	loadimage(&Gb_img[3][0], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Enemies\\Goomba\\goomba_rotateU0.png");
	loadimage(&Gb_img[3][1], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Enemies\\Goomba\\goomba_rotateU1.png");
}

void Goomba::put_img()
{
	for (int i = 0; i < Goomba::all_num; ++i)
	{
		if (Gb[i].y < WD_HEIGHT - Goomba_Length)			//当处于死亡状态且y超出屏幕时不用输出图片
		{
			if (Gb[i].state)			//存活（包括掉坑里未死亡）
			{
				if (Gb[i].direction == 1)
				{
					putimage(Gb[i].x - Map.x, Gb[i].y, Goomba_Length, Goomba_Length, &Gb_img[0][0], 0, 0, SRCAND);
					putimage(Gb[i].x - Map.x, Gb[i].y, Goomba_Length, Goomba_Length, &Gb_img[0][1], 0, 0, SRCPAINT);
				}
				else if (Gb[i].direction == 2)
				{
					putimage(Gb[i].x - Map.x, Gb[i].y, Goomba_Length, Goomba_Length, &Gb_img[1][0], 0, 0, SRCAND);
					putimage(Gb[i].x - Map.x, Gb[i].y, Goomba_Length, Goomba_Length, &Gb_img[1][1], 0, 0, SRCPAINT);
				}
			}

			else if (Gb[i].is_attack)									//被攻击弹飞
			{
				putimage(Gb[i].x - Map.x, Gb[i].y, Goomba_Length, Goomba_Length, &Gb_img[3][0], 0, 0, SRCAND);
				putimage(Gb[i].x - Map.x, Gb[i].y, Goomba_Length, Goomba_Length, &Gb_img[3][1], 0, 0, SRCPAINT);
			}
			
			else if(Gb[i].dead_showtime >= 0)		//死亡且未超出屏幕（被踩死）
			{
				putimage(Gb[i].x - Map.x, Gb[i].y, Goomba_Length, Goomba_Length, &Gb_img[2][0], 0, 0, SRCAND);
				putimage(Gb[i].x - Map.x, Gb[i].y, Goomba_Length, Goomba_Length, &Gb_img[2][1], 0, 0, SRCPAINT);
				--Gb[i].dead_showtime;
				if (Gb[i].dead_showtime == 0)
					Gb[i].y = WD_HEIGHT - Goomba_Length;
			}
		}
	}
}

bool Goomba::touch(const Collider& Mario, bool& trample, bool is_attack)
{
	for (int i = 0; i < Goomba::all_num; ++i)
	{
		if (!Gb[i].state) continue;
		if (Mario.x + Mario.length > Gb[i].x && Mario.x < Gb[i].x + Gb[i].length && Mario.y + Mario.height > Gb[i].y)		//触碰到
		{
			trample = false;
			if (is_attack)		//被攻击
			{
				Gb[i].state = false;
				Gb[i].is_attack = true;
				if (Mario.x + Mario.length < Gb[i].x + Gb[i].length / 2)		//往右运动
				{
					Gb[i].vx = 10;
					Gb[i].direction = 2;
				}
				else															//往左运动
				{
					Gb[i].vx = -10;
					Gb[i].direction = 1;
				}
				Gb[i].vy = -27;																//往上运动
			}
			else if ((Mario.x + Mario.length >= Gb[i].x + Gb[i].length / 5 && Mario.x <= Gb[i].x + Gb[i].length * 4 / 5 && Mario.y + Mario.length < Gb[i].y + Gb[i].length))	//被踩到
			{
				Gb[i].state = false;
				trample = true;
			}
			
			return true;
		}
	}
	return false;
}

void Goomba::up_date()
{
	for (int i = 0; i < Goomba::all_num; ++i)
	{
		//死亡
		if (Gb[i].is_attack)				//被攻击（已死亡，修改位置）
		{
			++Gb[i].stop_time;
			if (Gb[i].stop_time % 2 == 0)
			{
				Gb[i].y += Gb[i].vy;
				Gb[i].x += Gb[i].vx;
				Gb[i].vy += Gb[i].ay;
			}
		}
		if (!Gb[i].state) continue;

		//未死亡
		Gb[i].x += Gb[i].vx;
		//左边碰撞检测
		int left_pos;													
		bool left_check = Obstacle::is_collide_left(Gb[i], left_pos);
		if (Gb[i].direction == 1)
		{
			if (left_check)
			{
				Gb[i].x = left_pos;
				Gb[i].direction = 2;
				Gb[i].vx = -Gb[i].vx;
			}
			else if (Gb[i].x <= Gb[i].xl)
			{
				Gb[i].x = Gb[i].xl;
				Gb[i].direction = 2;
				Gb[i].vx = -Gb[i].vx;
			}
		}
		//右边碰撞检测
		int right_pos;
		bool right_check = Obstacle::is_collide_right(Gb[i], right_pos);
		if(Gb[i].direction == 2)
		{
			if (right_check)
			{
				Gb[i].x = right_pos - Goomba_Length;
				Gb[i].direction = 1;
				Gb[i].vx = -Gb[i].vx;
			}
			else if (Gb[i].x + Gb[i].length >= Gb[i].xr)
			{
				Gb[i].x = Gb[i].xr - Goomba_Length;
				Gb[i].direction = 1;
				Gb[i].vx = -Gb[i].vx;
			}
		}
		//下面检测
		Gb[i].y += Gb[i].vy;
		int down_pos;
		bool down_check = Obstacle::is_collide_down(Gb[i], down_pos);
		if (!down_check)			//下面是空的
		{
			Gb[i].vx = 0;
			Gb[i].vy = Gb[i].ay;
		}
	}
}

void Goomba::clear_manip()
{
	Gb[0].x =  800; Gb[1].x = 1000; Gb[2].x = 2000; Gb[3].x = 2850; Gb[4].x = 3500; Gb[5].x = 6200;
	Gb[6].x = 4800; Gb[7].x = 5900; Gb[8].x = 6050; Gb[9].x = 8000; Gb[10].x = 8200;
	for (int i = 0; i < all_num; ++i)
	{
		Gb[i].y = MAP_LAND - Goomba_Length; 
		Gb[i].state = true; 
		Gb[i].vx = -3; 
		Gb[i].direction = 1; 
		Gb[i].vy = 0;
		Gb[i].is_attack = false;
		Gb[i].dead_showtime = 25;
	}
}


//------------------------------------------------------------------------ Tortoise -------------------------------------------------------------------
Tortoise Tt[3] =
{
	{1900, MAP_LAND - Tortoise_Height_1, Tortoise_Length, Tortoise_Height_1, true, 1800, 2250},
	{3600, MAP_LAND - Tortoise_Height_1, Tortoise_Length, Tortoise_Height_1, true, 3500, 4000},
	{6650, MAP_LAND - Tortoise_Height_1, Tortoise_Length, Tortoise_Height_1, true, 6600, 6750}
};

void Tortoise::load_img()
{
	loadimage(&Tt_img[0][0], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Enemies\\Tortoise\\tortoiseL00.png");
	loadimage(&Tt_img[0][1], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Enemies\\Tortoise\\tortoiseL01.png");
	loadimage(&Tt_img[0][2], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Enemies\\Tortoise\\tortoiseL10.png");
	loadimage(&Tt_img[0][3], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Enemies\\Tortoise\\tortoiseL11.png");

	loadimage(&Tt_img[1][0], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Enemies\\Tortoise\\tortoiseR00.png");
	loadimage(&Tt_img[1][1], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Enemies\\Tortoise\\tortoiseR01.png");
	loadimage(&Tt_img[1][2], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Enemies\\Tortoise\\tortoiseR10.png");
	loadimage(&Tt_img[1][3], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Enemies\\Tortoise\\tortoiseR11.png");

	loadimage(&Tt_img[2][0], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Enemies\\Tortoise\\tortoiseD00.png");
	loadimage(&Tt_img[2][1], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Enemies\\Tortoise\\tortoiseD01.png");

	loadimage(&Tt_img[3][0], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Enemies\\Tortoise\\tortoise_rotateLU0.png");
	loadimage(&Tt_img[3][1], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Enemies\\Tortoise\\tortoise_rotateLU1.png");
	loadimage(&Tt_img[3][2], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Enemies\\Tortoise\\tortoise_rotateRU0.png");
	loadimage(&Tt_img[3][3], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Enemies\\Tortoise\\tortoise_rotateRU1.png");

}

void Tortoise::put_img()
{
	for (int i = 0; i < Tortoise::all_num; ++i)
	{
		if (Tt[i].y < WD_HEIGHT - Tt[i].height)			//当处于死亡状态且y超出屏幕时不用输出图片
		{
			if (Tt[i].form == 1)			//正常形态
			{
				if (!Tt[i].state)		//死亡
				{
					if (Tt[i].direction == 1)
					{
						putimage(Tt[i].x - Map.x, Tt[i].y, Tortoise_Length, Tortoise_Height_1, &Tt_img[3][0], 0, 0, SRCAND);
						putimage(Tt[i].x - Map.x, Tt[i].y, Tortoise_Length, Tortoise_Height_1, &Tt_img[3][1], 0, 0, SRCPAINT);
					}
					else
					{
						putimage(Tt[i].x - Map.x, Tt[i].y, Tortoise_Length, Tortoise_Height_1, &Tt_img[3][2], 0, 0, SRCAND);
						putimage(Tt[i].x - Map.x, Tt[i].y, Tortoise_Length, Tortoise_Height_1, &Tt_img[3][3], 0, 0, SRCPAINT);
					}
				}
				else
				{
					++Tt[i].step_time;
					if (Tt[i].direction == 1)
					{
						if (Tt[i].walk_step == 1)
						{
							putimage(Tt[i].x - Map.x, Tt[i].y, Tortoise_Length, Tortoise_Height_1, &Tt_img[0][0], 0, 0, SRCAND);
							putimage(Tt[i].x - Map.x, Tt[i].y, Tortoise_Length, Tortoise_Height_1, &Tt_img[0][1], 0, 0, SRCPAINT);
							if (Tt[i].step_time == 20)
							{
								Tt[i].step_time = 0;
								Tt[i].walk_step = 0;
							}
						}
						else
						{
							putimage(Tt[i].x - Map.x, Tt[i].y, Tortoise_Length, Tortoise_Height_1, &Tt_img[0][2], 0, 0, SRCAND);
							putimage(Tt[i].x - Map.x, Tt[i].y, Tortoise_Length, Tortoise_Height_1, &Tt_img[0][3], 0, 0, SRCPAINT);
							if (Tt[i].step_time == 20)
							{
								Tt[i].step_time = 0;
								Tt[i].walk_step = 1;
							}
						}
					}
					else
					{
						if (Tt[i].walk_step == 1)
						{
							putimage(Tt[i].x - Map.x, Tt[i].y, Tortoise_Length, Tortoise_Height_1, &Tt_img[1][0], 0, 0, SRCAND);
							putimage(Tt[i].x - Map.x, Tt[i].y, Tortoise_Length, Tortoise_Height_1, &Tt_img[1][1], 0, 0, SRCPAINT);
							if (Tt[i].step_time == 20)
							{
								Tt[i].step_time = 0;
								Tt[i].walk_step = 0;
							}
						}
						else
						{
							putimage(Tt[i].x - Map.x, Tt[i].y, Tortoise_Length, Tortoise_Height_1, &Tt_img[1][2], 0, 0, SRCAND);
							putimage(Tt[i].x - Map.x, Tt[i].y, Tortoise_Length, Tortoise_Height_1, &Tt_img[1][3], 0, 0, SRCPAINT);
							if (Tt[i].step_time == 20)
							{
								Tt[i].step_time = 0;
								Tt[i].walk_step = 1;
							}
						}
					}
				}
			}
			else			//龟壳
			{
				putimage(Tt[i].x - Map.x, Tt[i].y, Tortoise_Length, Tortoise_Height_2, &Tt_img[2][0], 0, 0, SRCAND);
				putimage(Tt[i].x - Map.x, Tt[i].y, Tortoise_Length, Tortoise_Height_2, &Tt_img[2][1], 0, 0, SRCPAINT);
			}
		}
	}
}

bool Tortoise::touch(const Collider& Mario, bool& trample, bool is_attack)
{
	for (int i = 0; i < Tortoise::all_num; ++i)
	{
		if (!Tt[i].state) continue;
		if (Mario.x + Mario.length > Tt[i].x && Mario.x < Tt[i].x + Tt[i].length && Mario.y + Mario.height > Tt[i].y)		//触碰到
		{
			trample = false;
			if (is_attack)
			{
				Tt[i].state = false;
				Tt[i].is_attack = true;
				if (Mario.x + Mario.length < Tt[i].x + Tt[i].length / 2)		//往右运动
				{
					Tt[i].vx = 7;
					Tt[i].direction = 2;
				}
				else															//往左运动
				{
					Tt[i].vx = -7;
					Tt[i].direction = 1;
				}
				Tt[i].vy = -27;
			}
			else if ((Mario.x + Mario.length >= Tt[i].x + Tt[i].length / 5 && Mario.x <= Tt[i].x + Tt[i].length * 4 / 5 && Mario.y + Mario.length < Tt[i].y + Tt[i].length))	//被踩到 / 被攻击
			{
				if (Tt[i].form == 1)		//变龟壳
				{
					Tt[i].form = 2;
					Tt[i].vx = 0;
					Tt[i].xl -= 1000;
					Tt[i].xr += 1000;
					Tt[i].y = MAP_LAND - Tortoise_Height_2;
					Tt[i].height = Tortoise_Height_2;
				}
				else						//停下来/继续运动
				{
					if (Tt[i].vx == 0)
					{
						Tt[i].vx = Tt[i].direction == 1 ? -Tt[i].vx_fast : Tt[i].vx_fast;
					}
					else
					{
						Tt[i].vx = 0;
					}
				}
				trample = true;
			}
			return true;
		}
	}
	return false;
}

void Tortoise::up_date()
{
	for (int i = 0; i < Tortoise::all_num; ++i)
	{
		//死亡
		if (Tt[i].is_attack)				//被攻击（已死亡，修改位置）
		{
			++Tt[i].stop_time;
			if (Tt[i].stop_time % 2 == 0)
			{
				Tt[i].y += Tt[i].vy;
				Tt[i].x += Tt[i].vx;
				Tt[i].vy += Tt[i].ay;
			}
		}
		if (!Tt[i].state) continue;
		
		//存活
		Tt[i].x += Tt[i].vx;
		
		if (Tt[i].form == 2 && Tt[i].vx != 0) { bool b; Goomba::touch(Tt[i], b, true); }		//与goomba碰撞检测（对Tortoise无影响）

		//左边碰撞检测
		int left_pos;
		bool left_check = Obstacle::is_collide_left(Tt[i], left_pos);
		if (Tt[i].direction == 1)
		{
			if (left_check)
			{
				Tt[i].x = left_pos;
				Tt[i].direction = 2;
				Tt[i].vx = -Tt[i].vx;
			}
			else if (Tt[i].x <= Tt[i].xl)
			{
				Tt[i].x = Tt[i].xl;
				Tt[i].direction = 2;
				Tt[i].vx = -Tt[i].vx;
			}
		}
		//右边碰撞检测
		int right_pos;
		bool right_check = Obstacle::is_collide_right(Tt[i], right_pos);
		if (Tt[i].direction == 2)
		{
			if (right_check)
			{
				Tt[i].x = right_pos - Tt[i].length;
				Tt[i].direction = 1;
				Tt[i].vx = -Tt[i].vx;
			}
			else if (Tt[i].x + Tt[i].length >= Tt[i].xr)
			{
				Tt[i].x = Tt[i].xr - Tt[i].length;
				Tt[i].direction = 1;
				Tt[i].vx = -Tt[i].vx;
			}
		}
		//下面检测
		Tt[i].y += Tt[i].vy;
		int down_pos;
		bool down_check = Obstacle::is_collide_down(Tt[i], down_pos);
		if (!down_check)			//下面是空的
		{
			Tt[i].vy = Tt[i].ay;
		}
	}
}

void Tortoise::clear_manip()
{
	Tt[0].x = 1900; Tt[0].xl = 1800; Tt[0].xr = 2250; Tt[0].form = 1;
	Tt[1].x = 3600; Tt[1].xl = 3500; Tt[1].xr = 4000; Tt[1].form = 1;
	Tt[2].x = 6650; Tt[2].xl = 6600; Tt[2].xr = 6750; Tt[2].form = 1;
	for (int i = 0; i < all_num; ++i)
	{
		Tt[i].state = true;
		Tt[i].height = Tortoise_Height_1; 
		Tt[i].y = MAP_LAND - Tortoise_Height_1; 
		Tt[i].vx = -3; 
		Tt[i].direction = 1; 
		Tt[i].vy = 0;
		Tt[i].is_attack = false;
		Tt[i].stop_time = 0;
	}
}


//------------------------------------------------------------------------ Piranha -------------------------------------------------------------------
Piranha Ph[3] =
{
	{1851, MAP_LAND - Pipe_Height_2, Piranha_Length, Piranha_Height, true},
	{7850, MAP_LAND - Pipe_Height_1, Piranha_Length, Piranha_Height, true},
	{8617, MAP_LAND - Pipe_Height_1, Piranha_Length, Piranha_Height, true}
};

void Piranha::load_img()
{
	loadimage(&Ph_img[0][0], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Enemies\\Piranha\\PiranhaUP00.png");
	loadimage(&Ph_img[0][1], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Enemies\\Piranha\\PiranhaUP01.png");
	loadimage(&Ph_img[0][2], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Enemies\\Piranha\\PiranhaUP10.png");
	loadimage(&Ph_img[0][3], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Enemies\\Piranha\\PiranhaUP11.png");

	loadimage(&Ph_img[1][0], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Enemies\\Piranha\\PiranhaDN00.png");
	loadimage(&Ph_img[1][1], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Enemies\\Piranha\\PiranhaDN01.png");
	loadimage(&Ph_img[1][2], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Enemies\\Piranha\\PiranhaDN10.png");
	loadimage(&Ph_img[1][3], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Enemies\\Piranha\\PiranhaDN11.png");
}

void Piranha::put_img()
{
	for (int i = 0; i < Piranha::all_num; ++i)
	{
		if (!Ph[i].state)		//死亡
		{
			putimage(Ph[i].x - Map.x, Ph[i].y, Ph[i].length, Ph[i].height, &Ph_img[1][2], 0, 0, SRCAND);
			putimage(Ph[i].x - Map.x, Ph[i].y, Ph[i].length, Ph[i].height, &Ph_img[1][3], 0, 0, SRCPAINT);
			continue;
		}

		if (Ph[i].direction < 1) continue;
		++Ph[i].step_time;
		if (Ph[i].walk_step == 0)
		{
			putimage(Ph[i].x - Map.x, Ph[i].y - Ph[i].y_show, Ph[i].length, Ph[i].y_show, &Ph_img[0][0], 0, 0, SRCAND);
			putimage(Ph[i].x - Map.x, Ph[i].y - Ph[i].y_show, Ph[i].length, Ph[i].y_show, &Ph_img[0][1], 0, 0, SRCPAINT);
			if (Ph[i].step_time == 20)
			{
				Ph[i].step_time = 0;
				Ph[i].walk_step = 1;
			}
		}
		else
		{
			putimage(Ph[i].x - Map.x, Ph[i].y - Ph[i].y_show, Ph[i].length, Ph[i].y_show, &Ph_img[0][2], 0, 0, SRCAND);
			putimage(Ph[i].x - Map.x, Ph[i].y - Ph[i].y_show, Ph[i].length, Ph[i].y_show, &Ph_img[0][3], 0, 0, SRCPAINT);
			if (Ph[i].step_time == 20)
			{
				Ph[i].step_time = 0;
				Ph[i].walk_step = 0;
			}
		}
	}
}

bool Piranha::touch(const Collider& Mario, bool& trample, bool is_attack)
{
	trample = false;
	for (int i = 0; i < Piranha::all_num; ++i)
	{
		if (!Ph[i].state) continue;

		if (Ph[i].direction >= 1 && Mario.x + Mario.length > Ph[i].x && Mario.x < Ph[i].x + Ph[i].length && Mario.y + Mario.height > Ph[i].y - Ph[i].y_show)
		{
			if (is_attack)		//被攻击
			{
				Ph[i].state = false;
				Ph[i].is_attack = true;
				if (Mario.x + Mario.length < Ph[i].x + Ph[i].length / 2)		//往右运动
				{
					Ph[i].vx = 10;
					Ph[i].direction = 4;
				}
				else															//往左运动
				{
					Ph[i].vx = -10;
					Ph[i].direction = 3;
				}
				Ph[i].vy = -27;																//往上运动
			}
			return true;
		}
	}
	return false;
}

void Piranha::up_date()
{
	for (int i = 0; i < Piranha::all_num; ++i)
	{
		//死亡
		if (Ph[i].is_attack)				//被攻击（已死亡，修改位置）
		{
			++Ph[i].stop_time;
			if (Ph[i].stop_time % 2 == 0)
			{
				Ph[i].y += Ph[i].vy;
				Ph[i].x += Ph[i].vx;
				Ph[i].vy += Ph[i].ay;
			}
		}
		if (!Ph[i].state) continue;

		if (Ph[i].direction < 1)			//停留
		{
			++Ph[i].direction;
		}
		else if (Ph[i].direction == 1)		//向上运动
		{
			if (Ph[i].y_show == Piranha_Height)		//运动到顶端
			{
				Ph[i].direction = 2;
			}
			else
			{
				Ph[i].y_show += Ph[i].vy;
			}
		}
		else if (Ph[i].direction == 2)		//向下运动
		{
			if (Ph[i].y_show == 0)					//运动到底端
			{
				Ph[i].direction = -100;
			}
			else
			{
				Ph[i].y_show -= Ph[i].vy;
			}
		}
	}
}

void Piranha::clear_manip()
{
	Ph[0].x = 1851; Ph[1].x = 7850; Ph[2].x = 8617;
	Ph[0].y = MAP_LAND - Pipe_Height_2; Ph[1].y = MAP_LAND - Pipe_Height_1; Ph[2].y = MAP_LAND - Pipe_Height_1;
	for (int i = 0; i < Piranha::all_num; ++i)
	{
		Ph[i].state = true;
		Ph[i].direction = 1;
		Ph[i].y_show = 0;
		Ph[i].walk_step = 0;
		Ph[i].vx = 0;
		Ph[i].vy = 1;
		Ph[i].is_attack = false;
	}
}