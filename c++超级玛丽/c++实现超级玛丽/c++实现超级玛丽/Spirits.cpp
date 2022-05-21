#include "Spirits.h"
#include "Bkground.h"

#include <iostream>

IMAGE combrick_img[2];		
IMAGE spebrick_img[2][2];
IMAGE coinbrick_img[2];
IMAGE mushbrick_img[2];
IMAGE flowbrick_img[2];
IMAGE starbrick_img[2];
IMAGE coin_img[2];
IMAGE pole_img[2];
IMAGE flag_img[2];

//---------------------------------------------------------- 普通砖块（固定住的） ----------------------------------------------------------------------------
Com_Brick Combrick[Com_Brick::all_num] =
{
	{702, 400, Brick_Length, Brick_Length, true},
	{750, 400, Brick_Length, Brick_Length, true},
	{846, 400, Brick_Length, Brick_Length, true},
	{942, 400, Brick_Length, Brick_Length, true},
	{990, 400, Brick_Length, Brick_Length, true},

	{3178, 400, Brick_Length, Brick_Length, true},
	{3530, 400, Brick_Length, Brick_Length, true},
	{3626, 400, Brick_Length, Brick_Length, true},

	{3626 + 48 * 2, 240, Brick_Length, Brick_Length, true},
	{3626 + 48 * 3, 240, Brick_Length, Brick_Length, true},
	{3626 + 48 * 4, 240, Brick_Length, Brick_Length, true},
	{3626 + 48 * 5, 240, Brick_Length, Brick_Length, true},
	{3626 + 48 * 6, 240, Brick_Length, Brick_Length, true},
	{3626 + 48 * 7, 240, Brick_Length, Brick_Length, true},
	{3626 + 48 * 8, 240, Brick_Length, Brick_Length, true},
	{3626 + 48 * 9, 240, Brick_Length, Brick_Length, true},
	{3626 + 48 * 10, 240, Brick_Length, Brick_Length, true},
	{3626 + 48 * 11, 240, Brick_Length, Brick_Length, true},

	{3626 + 48 * 15, 240, Brick_Length, Brick_Length, true},
	{3626 + 48 * 16, 240, Brick_Length, Brick_Length, true},
	{3626 + 48 * 17, 240, Brick_Length, Brick_Length, true},
	{3626 + 48 * 18, 240, Brick_Length, Brick_Length, true},

	{4526 + 48 * 2, 400, Brick_Length, Brick_Length, true},
	{4526 + 48 * 3, 400, Brick_Length, Brick_Length, true},
	{4526 + 48 * 4, 400, Brick_Length, Brick_Length, true},

	{5426 + 48 * 2, 400, Brick_Length, Brick_Length, true},

	{9290 + 48 * 0, 100, Brick_Length, Brick_Length, true},
	{9290 + 48 * 1, 100, Brick_Length, Brick_Length, true},
	{9300, 340, Brick_Length, Brick_Length, true},
};

void Com_Brick::load_img()
{
	loadimage(&combrick_img[0], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Spirits\\Brick\\brickwithnothing0.png");		//什么都没有的砖块
	loadimage(&combrick_img[1], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Spirits\\Brick\\brickwithnothing1.png");
}

void Com_Brick::init()
{
	load_img();
}

void Com_Brick::put_img()
{
	for (int i = 0; i < all_num; ++i)
	{
		putimage(Combrick[i].x - Map.x, Combrick[i].y, Combrick[i].length, Combrick[i].height, &combrick_img[0], 0, 0, SRCAND);
		putimage(Combrick[i].x - Map.x, Combrick[i].y, Combrick[i].length, Combrick[i].height, &combrick_img[1], 0, 0, SRCPAINT);
	}
}


//碰撞检测（o会动，碰撞到砖块）
bool Com_Brick::is_collide_left(const Collider& o, int& left_pos)
{
	for(int i = 0; i < all_num; ++i)
		if (o.y + o.height > Combrick[i].y && o.y < Combrick[i].y + Combrick[i].height && o.x <= Combrick[i].x + Combrick[i].length && o.x + o.length > Combrick[i].x)
		{
			left_pos = Combrick[i].x + Combrick[i].length;
			return true;
		}
	return false;
}

bool Com_Brick::is_collide_right(const Collider& o, int& right_pos)
{
	for (int i = 0; i < all_num; ++i)
		if (o.y + o.height > Combrick[i].y && o.y < Combrick[i].y + Combrick[i].height && o.x + o.length >= Combrick[i].x && o.x < Combrick[i].x + Combrick[i].length)
		{
			right_pos = Combrick[i].x;
			return true;
		}
	return false;
}

bool Com_Brick::is_collide_down(const Collider& o, int& down_pos)
{
	for(int i = 0; i < all_num; ++i)
		if (o.x + o.length > Combrick[i].x && o.x < Combrick[i].x + Combrick[i].length && o.y < Combrick[i].y + Combrick[i].height && o.y + o.height >= Combrick[i].y)
		{
			down_pos = Combrick[i].y;
			return true;
		}
	return false;
}

bool Com_Brick::is_collide_up(const Collider& o, int& up_pos)
{
	for(int i = 0; i < all_num; ++i)
		if (o.x + o.length > Combrick[i].x && o.x < Combrick[i].x + Combrick[i].length && o.y + o.height > Combrick[i].y && o.y <= Combrick[i].y + Combrick[i].height)
		{
			up_pos = Combrick[i].y + Combrick[i].length;
			return true;
		}
	return false;
}



//---------------------------------------------------------- 特殊砖块 ----------------------------------------------------------------------------
Spe_Brick Spebrick[Spe_Brick::all_num] =
{
	/*(x, y, len, hei, state, 是否触发，种类(0无，1金币，2蘑菇，3星星，4花朵)，特殊物品数目，位置)*/
	{798, 400, Brick_Length, Brick_Length, true, 0, 1, 3, 2},
	{894, 400, Brick_Length, Brick_Length, true, 0, 2, 1, 1},
	{846, 150, Brick_Length, Brick_Length, true, 0, 1, 3, 3},

	{3130, 400, Brick_Length, Brick_Length, true, 0, 4, 1, 0},
	{3578, 400, Brick_Length, Brick_Length, true, 0, 1, 3, 1},

	{4718 + 4 * Brick_Length, 400, Brick_Length, Brick_Length, true, 0, 1, 3, 2},
	{4718 + 8 * Brick_Length, 400, Brick_Length, Brick_Length, true, 0, 1, 3, 3},
	{4718 + 12 * Brick_Length, 400, Brick_Length, Brick_Length, true, 0, 1, 3, 3},

	{5426 + 3 * Brick_Length, 400, Brick_Length, Brick_Length, true, 0, 3, 1, 0},

	{5618 + 4 * Brick_Length, 400, Brick_Length, Brick_Length, true, 0, 1, 3, 0},
	{5618 + 8 * Brick_Length, 400, Brick_Length, Brick_Length, true, 0, 1, 3, 1},
	{5618 + 12 * Brick_Length, 400, Brick_Length, Brick_Length, true, 0, 1, 3, 2}
};


void Spe_Brick::load_img()
{
	loadimage(&spebrick_img[0][0], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Spirits\\Brick\\brickwithnothing0.png");		//花纹砖块
	loadimage(&spebrick_img[0][1], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Spirits\\Brick\\commonbrick.png");

	loadimage(&spebrick_img[1][0], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Spirits\\Brick\\brickwithnothing0.png");		//四个一起的问号砖块
	loadimage(&spebrick_img[1][1], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Spirits\\Brick\\specialbrick.png");

	loadimage(&coinbrick_img[0], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Spirits\\Brick\\coinbrick0.png");				//四个金币砖块
	loadimage(&coinbrick_img[1], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Spirits\\Brick\\coinbrick1.png");

	loadimage(&mushbrick_img[0], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Spirits\\Brick\\mushroom0.png");					//蘑菇砖块
	loadimage(&mushbrick_img[1], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Spirits\\Brick\\mushroom1.png");

	loadimage(&flowbrick_img[0], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Spirits\\Brick\\star0.png");						//四个星星砖块
	loadimage(&flowbrick_img[1], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Spirits\\Brick\\star1.png");

	loadimage(&starbrick_img[0], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Spirits\\Brick\\flower0.png");					//四个花朵砖块
	loadimage(&starbrick_img[1], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Spirits\\Brick\\flower1.png");
}

void Spe_Brick::init()
{
	load_img();
}

void Spe_Brick::put_img()
{
	for (int i = 0; i < all_num; ++i)
	{
		if (Spebrick[i].kind == 0 || Spebrick[i].kind == 1)
		{
			putimage(Spebrick[i].x - Map.x, Spebrick[i].y + Spebrick[i].y_move, Spebrick[i].length, Spebrick[i].height, &spebrick_img[0][0], 0, 0, SRCAND);
			putimage(Spebrick[i].x - Map.x, Spebrick[i].y + Spebrick[i].y_move, Spebrick[i].length, Spebrick[i].height, &spebrick_img[0][1], 0, 0, SRCPAINT);
			if (Spebrick[i].trigger)
			{
				if (Spebrick[i].spnum >= 0)
				{
					putimage(Spebrick[i].x - Map.x, Spebrick[i].y + Spebrick[i].y_move - Brick_Length, Spebrick[i].length, Spebrick[i].height, &coinbrick_img[0], Spebrick[i].place * Brick_Length, 0, SRCAND);
					putimage(Spebrick[i].x - Map.x, Spebrick[i].y + Spebrick[i].y_move - Brick_Length, Spebrick[i].length, Spebrick[i].height, &coinbrick_img[1], Spebrick[i].place * Brick_Length, 0, SRCPAINT);
				}
				Spebrick[i].trigger = 0;		//金币砖块每次触发完后变回未触发
			}
		}
		else
		{
			if (!Spebrick[i].trigger)		//未触发
			{
				putimage(Spebrick[i].x - Map.x, Spebrick[i].y + Spebrick[i].y_move, Spebrick[i].length, Spebrick[i].height, &spebrick_img[1][0], 0, 0, SRCAND);
				putimage(Spebrick[i].x - Map.x, Spebrick[i].y + Spebrick[i].y_move, Spebrick[i].length, Spebrick[i].height, &spebrick_img[1][1], Spebrick[i].place * Brick_Length, 0, SRCPAINT);
			}	
			else							//已触发
			{
				putimage(Spebrick[i].x - Map.x, Spebrick[i].y, Spebrick[i].length, Spebrick[i].height, &combrick_img[0], 0, 0, SRCAND);
				putimage(Spebrick[i].x - Map.x, Spebrick[i].y, Spebrick[i].length, Spebrick[i].height, &combrick_img[1], 0, 0, SRCPAINT);
				if (Spebrick[i].state)
				{
					switch (Spebrick[i].kind) {
					case 1:
						putimage(Spebrick[i].x - Map.x, Spebrick[i].y + Spebrick[i].y_move, Spebrick[i].length, Spebrick[i].height, &coinbrick_img[0], 0, 0, SRCAND);
						putimage(Spebrick[i].x - Map.x, Spebrick[i].y + Spebrick[i].y_move, Spebrick[i].length, Spebrick[i].height, &coinbrick_img[1], Spebrick[i].place * Brick_Length, 0, SRCPAINT);
						break;
					case 2:
						putimage(Spebrick[i].x - Map.x, Spebrick[i].y + Spebrick[i].y_move, Spebrick[i].length, Spebrick[i].height, &mushbrick_img[0], 0, 0, SRCAND);
						putimage(Spebrick[i].x - Map.x, Spebrick[i].y + Spebrick[i].y_move, Spebrick[i].length, Spebrick[i].height, &mushbrick_img[1], 0, 0, SRCPAINT);
						break;
					case 3:
						putimage(Spebrick[i].x - Map.x, Spebrick[i].y + Spebrick[i].y_move, Spebrick[i].length, Spebrick[i].height, &flowbrick_img[0], 0, 0, SRCAND);
						putimage(Spebrick[i].x - Map.x, Spebrick[i].y + Spebrick[i].y_move, Spebrick[i].length, Spebrick[i].height, &flowbrick_img[1], Spebrick[i].place * Brick_Length, 0, SRCPAINT);
						break;
					case 4:
						putimage(Spebrick[i].x - Map.x, Spebrick[i].y + Spebrick[i].y_move, Spebrick[i].length, Spebrick[i].height, &starbrick_img[0], 0, 0, SRCAND);
						putimage(Spebrick[i].x - Map.x, Spebrick[i].y + Spebrick[i].y_move, Spebrick[i].length, Spebrick[i].height, &starbrick_img[1], Spebrick[i].place * Brick_Length, 0, SRCPAINT);
						break;
					default:
						break;
					}
				}
			}
		}
	}
}


//碰撞检测（o会动，碰撞到砖块）
bool Spe_Brick::is_collide_left(const Collider& o, int& left_pos)
{
	for (int i = 0; i < all_num; ++i)
		if (o.y + o.height > Spebrick[i].y && o.y < Spebrick[i].y + Spebrick[i].height && o.x <= Spebrick[i].x + Spebrick[i].length && o.x + o.length > Spebrick[i].x)
		{
			left_pos = Spebrick[i].x + Spebrick[i].length;
			return true;
		}
	return false;
}

bool Spe_Brick::is_collide_right(const Collider& o, int& right_pos)
{
	for (int i = 0; i < all_num; ++i)
		if (o.y + o.height > Spebrick[i].y && o.y < Spebrick[i].y + Spebrick[i].height && o.x + o.length >= Spebrick[i].x && o.x < Spebrick[i].x + Spebrick[i].length)
		{
			right_pos = Spebrick[i].x;
			return true;
		}
	return false;
}

bool Spe_Brick::is_collide_down(const Collider& o, int& down_pos)
{
	for (int i = 0; i < all_num; ++i)
		if (o.x + o.length > Spebrick[i].x && o.x < Spebrick[i].x + Spebrick[i].length && o.y < Spebrick[i].y + Spebrick[i].height && o.y + o.height >= Spebrick[i].y)
		{
			down_pos = Spebrick[i].y;
			return true;
		}
	return false;
}

bool Spe_Brick::is_collide_up(const Collider& o, int& up_pos)		//增加每个砖块运动情况
{
	for (int i = 0; i < all_num; ++i)
	{
		Spebrick[i].y_move += Spebrick[i].vy;		//特殊砖块的运动
		if (Spebrick[i].is_jump)
		{
			Spebrick[i].vy += Spebrick[i].ay;
			if ((Spebrick[i].kind == 0 || Spebrick[i].kind == 1) && Spebrick[i].y_move == 0)	//0,1砖块会回到原位
			{
				Spebrick[i].is_jump = 0;
				Spebrick[i].vy = 0;
			}
			else if ((Spebrick[i].kind == 2 || Spebrick[i].kind == 3 || Spebrick[i].kind == 4) && -Spebrick[i].y_move >= Brick_Length)	//2,3,4会上移一个位置
			{
				Spebrick[i].is_jump = 0;
				Spebrick[i].vy = 0;
				Spebrick[i].y_move = -Brick_Length;
			}
		}
		if (o.x + o.length > Spebrick[i].x && o.x < Spebrick[i].x + Spebrick[i].length && o.y + o.height > Spebrick[i].y && o.y <= Spebrick[i].y + Spebrick[i].height)
		{
			if (!Spebrick[i].is_jump)				//顶到了砖块
			{
				if (!Spebrick[i].trigger)			//若砖块未触发,砖块（或物品）向上运动
				{
					Spebrick[i].is_jump = 1;
					--Spebrick[i].spnum;
					Spebrick[i].trigger = 1;
					if (Spebrick[i].kind == 0 || Spebrick[i].kind == 1)
					{
						Spebrick[i].vy = -Spebrick[i].vy_max;
						//if (Spebrick[i].kind == 1 && Spebrick[i].spnum >= 0)		//有金币
						//{
						//	Mali.mci_coin_sound = 30;
						//	++Mali.mci_coin_times;
						//}
					}
					else if (Spebrick[i].kind == 2 || Spebrick[i].kind == 3 || Spebrick[i].kind == 4)		//问号砖块不会动，但里面的物品会动
					{
						Spebrick[i].vy = -2 * Spebrick[i].vy_max;
						Mali.mci_magic_sound = 50;
						++Mali.mci_magic_times;
					}
				}
			}
			up_pos = Spebrick[i].y + Spebrick[i].height;
			return true;
		}
	}
	return false;
}

void Spe_Brick::eat(Mario& Mali)
{
	for (int i = 0; i < all_num; ++i)
	{
		if (!Spebrick[i].state) continue;
		if (Spebrick[i].kind == 2 || Spebrick[i].kind == 3 || Spebrick[i].kind == 4)
		{
			if (Mali.x + Mali.length > Spebrick[i].x && Mali.x < Spebrick[i].x + Spebrick[i].length && Mali.y + Mali.height > Spebrick[i].y + Spebrick[i].y_move && Mali.y < Spebrick[i].y)
			{
				Spebrick[i].state = false;
				if ((Spebrick[i].kind == 2 || Spebrick[i].kind == 4) && Mali.height == Mario_Small_Height)		//变大
				{
					Mali.height = Mario_Big_Height;
					Mali.y -= Mario_Big_Height - Mario_Small_Height;
				}
				if (Spebrick[i].kind == 3 && Mali.height == Mario_Big_Height)		//变无敌（变小）
				{
					Mali.height = Mario_Small_Height;
					Mali.y += Mario_Big_Height - Mario_Small_Height;
				}
				Mali.buffer = Spebrick[i].kind - 1;
				Mali.buffer_time = 0;
				Mali.mci_turn_sound = 30;
				++Mali.mci_turn_times;
			}
		}
	}
}

void Spe_Brick::clear_manip()
{
	Spebrick[0].state = true; Spebrick[0].trigger = 0; Spebrick[0].spnum = 3; Spebrick[0].y_move = 0;
	Spebrick[1].state = true; Spebrick[1].trigger = 0; Spebrick[1].spnum = 1; Spebrick[1].y_move = 0;
	Spebrick[2].state = true; Spebrick[2].trigger = 0; Spebrick[2].spnum = 3; Spebrick[2].y_move = 0;
	 
	Spebrick[3].state = true; Spebrick[3].trigger = 0; Spebrick[3].spnum = 1; Spebrick[3].y_move = 0;
	Spebrick[4].state = true; Spebrick[4].trigger = 0; Spebrick[4].spnum = 3; Spebrick[4].y_move = 0;

	Spebrick[5].state = true; Spebrick[5].trigger = 0; Spebrick[5].spnum = 3; Spebrick[5].y_move = 0; 
	Spebrick[6].state = true; Spebrick[6].trigger = 0; Spebrick[6].spnum = 1; Spebrick[6].y_move = 0;
	Spebrick[7].state = true; Spebrick[7].trigger = 0; Spebrick[7].spnum = 3; Spebrick[7].y_move = 0;

	Spebrick[8].state = true; Spebrick[8].trigger = 0; Spebrick[8].spnum = 1; Spebrick[8].y_move = 0;

	Spebrick[9].state = true; Spebrick[9].trigger = 0; Spebrick[9].spnum = 3; Spebrick[9].y_move = 0;
	Spebrick[10].state = true; Spebrick[10].trigger = 0; Spebrick[10].spnum = 3; Spebrick[10].y_move = 0;
	Spebrick[11].state = true; Spebrick[11].trigger = 0; Spebrick[11].spnum = 3; Spebrick[11].y_move = 0;
}



//---------------------------------------------------------- 金币 ----------------------------------------------------------------------------
Coin Cn[Coin::all_num] =
{
	{702 + 48 * 0, 400 - 48, Coin_Length, Coin_Length, true, 0},
	{702 + 48 * 1, 400 - 48, Coin_Length, Coin_Length, true, 1},
	{702 + 48 * 2, 400 - 48, Coin_Length, Coin_Length, true, 2},
	{702 + 48 * 3, 400 - 48, Coin_Length, Coin_Length, true, 3},

	{3770 + 48 * 0, 240 - 48, Coin_Length, Coin_Length, true, 0},
	{3770 + 48 * 1, 240 - 48, Coin_Length, Coin_Length, true, 1},
	{3770 + 48 * 2, 240 - 48, Coin_Length, Coin_Length, true, 2},
	{3770 + 48 * 3, 240 - 48, Coin_Length, Coin_Length, true, 3},
};

void Coin::load_img()
{
	loadimage(&coin_img[0], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Spirits\\Coin\\coin0.png");
	loadimage(&coin_img[1], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Spirits\\Coin\\coin1.png");
}

void Coin::init()
{
	load_img();
}

void Coin::put_img()
{
	for (int i = 0; i < all_num; ++i)
	{
		if (!Cn[i].state) continue;
		putimage(Cn[i].x - Map.x, Cn[i].y, Cn[i].length, Cn[i].height, &coin_img[0], Cn[i].place * 48, 0, SRCAND);
		putimage(Cn[i].x - Map.x, Cn[i].y, Cn[i].length, Cn[i].height, &coin_img[1], Cn[i].place * 48, 0, SRCPAINT);
	}
}

void Coin::eat(Mario& Mali)
{
	for (int i = 0; i < all_num; ++i)
	{
		if (!Cn[i].state) continue;
		if (Mali.x + Mali.length > Cn[i].x && Mali.x < Cn[i].x + Cn[i].length && Mali.y + Mali.height > Cn[i].y && Mali.y + Mali.height <= Cn[i].y + Cn[i].height)
		{
			Cn[i].state = false;
			Mali.mci_coin_sound = 30;
			++Mali.mci_coin_times;
		}
	}
}

void Coin::clear_manip()
{
	for (int i = 0; i < all_num; ++i)
	{
		Cn[i].state = true;
	}
}




//---------------------------------------------------------- 旗帜 ----------------------------------------------------------------------------
Flag Fl[1] =
{
	{9526 - Flag_Length, MAP_LAND - Brick_Length - Pole_Height, Flag_Length, Flag_Length, true, MAP_LAND - Brick_Length, false}
};

void Flag::load_img()
{
	loadimage(&pole_img[0], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Spirits\\Flag\\pole0.png");
	loadimage(&pole_img[1], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Spirits\\Flag\\pole1.png");

	loadimage(&flag_img[0], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Spirits\\Flag\\flag0.png");
	loadimage(&flag_img[1], "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\Spirits\\Flag\\flag1.png");
}

void Flag::init()
{
	load_img();
}

void Flag::put_img()
{
	for (int i = 0; i < all_num; ++i)
	{
		//旗杆
		putimage(Fl[i].x + Flag_Length - 5 - Map.x, Fl[i].y_ground - Pole_Height, 14, Pole_Height, &pole_img[0], 37, 14, SRCAND);
		putimage(Fl[i].x + Flag_Length - 5 - Map.x, Fl[i].y_ground - Pole_Height, 14, Pole_Height, &pole_img[1], 37, 14, SRCPAINT);
		//旗帜
		putimage(Fl[i].x - Map.x, Fl[i].y, Fl[i].length, Fl[i].height, &flag_img[0], 0, 0, SRCAND);
		putimage(Fl[i].x - Map.x, Fl[i].y, Fl[i].length, Fl[i].height, &flag_img[1], 0, 0, SRCPAINT);
	}
}

bool Flag::is_touch(Mario& Mali)
{
	for (int i = 0; i < all_num; ++i)
	{
		if (!Fl[i].state) continue;
		if (Mali.x + Mali.length >= Fl[i].x + Fl[i].length && Mali.x <= Fl[i].x + Fl[i].length + Pole_Length && Mali.y + Mali.length >= Fl[i].y_ground - Pole_Height)
		{
			mciSendString("open E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\music\\flagpole.mp3 alias flag", NULL, 0, NULL);
			mciSendString("play flag repeat", NULL, 0, NULL);
			if (Fl[i].y + Fl[i].height >= Fl[i].y_ground)
			{
				mciSendString("close flag", NULL, 0, NULL);
				Fl[i].y = Fl[i].y_ground - Fl[i].height;
				Fl[i].state = false;
				return false;
			}
			Fl[i].y += Fl[i].vy;
			Mali.y += Fl[i].vy;
			if (Mali.y + Mali.height >= Fl[i].y_ground)
			{
				Mali.y = Fl[i].y_ground - Mali.height;
			}
			return true;
		}
	}
	return false;
}

void Flag::clear_manip()
{
	Fl[0].y = MAP_LAND - Brick_Length - Pole_Height;
	for (int i = 0; i < all_num; ++i)
	{
		Fl[i].state = true;
	}
}