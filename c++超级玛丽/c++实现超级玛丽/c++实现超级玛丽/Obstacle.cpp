//掉进坑里不应该死掉，要直接掉下去，掉到一定距离就直接清除

#include "Obstacle.h"
#include "Bkground.h"
#include <iostream>
extern Bkground Map;

Obstacle Brick[Obstacle::All_Kind] = {
	{2,					//左右下边界（下边界可不用）
		{{0, 0}, {Map.length - MAP_EXTRA, 0}, {0, WD_HEIGHT}},
		{{0, WD_HEIGHT}, {Map.length - MAP_EXTRA, WD_HEIGHT}, {Map.length - MAP_EXTRA, WD_HEIGHT}}
	},

	{4,					//地板
		{{0, MAP_LAND}, {3302 + 110, MAP_LAND}, {4118 + 164, MAP_LAND}, {7330 + 136, MAP_LAND}},
		{{3302, WD_HEIGHT}, {4118, WD_HEIGHT}, {7330, WD_HEIGHT}, {Map.length - MAP_EXTRA, WD_HEIGHT}}
	},

	{6,					//水管
		{{1347, MAP_LAND - Pipe_Height_1}, {1828, MAP_LAND - Pipe_Height_2}, {2212, MAP_LAND - Pipe_Height_3}, {2739, MAP_LAND - Pipe_Height_3},
			{7827, MAP_LAND - Pipe_Height_1}, {8594, MAP_LAND - Pipe_Height_1}},
		{{1343 + Pipe_Lenght, MAP_LAND}, {1824 + Pipe_Lenght, MAP_LAND}, {2208 + Pipe_Lenght, MAP_LAND}, {2735 + Pipe_Lenght, MAP_LAND},
			{7823 + Pipe_Lenght, MAP_LAND}, {8590 + Pipe_Lenght, MAP_LAND}}
	},

	{25,				//楼梯(一列一列算）
		{{6437, MAP_LAND - Brick_Height}, {6437 + Brick_Length, MAP_LAND - 2 * Brick_Height}, {6437 + 2 * Brick_Length, MAP_LAND - 3 * Brick_Height}, {6437 + 3 * Brick_Length, MAP_LAND - 4 * Brick_Height},
			{6725, MAP_LAND - 4 * Brick_Height}, {6725 + Brick_Length, MAP_LAND - 3 * Brick_Height}, {6725 + 2 * Brick_Length, MAP_LAND - 2 * Brick_Height}, {6725 + 3 * Brick_Length, MAP_LAND - Brick_Height},
			{7109, MAP_LAND - Brick_Height}, {7109 + Brick_Length, MAP_LAND - 2 * Brick_Height}, {7109 + 2 * Brick_Length, MAP_LAND - 3 * Brick_Height}, {7109 + 3 * Brick_Length, MAP_LAND - 4 * Brick_Height},
			{7445, MAP_LAND - 4 * Brick_Height}, {7445 + Brick_Length, MAP_LAND - 3 * Brick_Height}, {7445 + 2 * Brick_Length, MAP_LAND - 2 * Brick_Height}, {7445 + 3 * Brick_Length, MAP_LAND - Brick_Height},
			{8692, MAP_LAND - Brick_Height}, {8692 + Brick_Length, MAP_LAND - 2 * Brick_Height}, {8692 + 2 * Brick_Length, MAP_LAND - 3 * Brick_Height}, {8692 + 3 * Brick_Length, MAP_LAND - 4 * Brick_Height}, {8692 + 4 * Brick_Length, MAP_LAND - 5 * Brick_Height},
				{8692 + 5 * Brick_Length, MAP_LAND - 6 * Brick_Height}, {8692 + 6 * Brick_Length, MAP_LAND - 7 * Brick_Height}, {8692 + 7 * Brick_Length, MAP_LAND - 8 * Brick_Height},
			{9509, MAP_LAND - Brick_Height}},
		{{6432 + Brick_Length-5, MAP_LAND}, {6432 + 2 * Brick_Length - 5, MAP_LAND}, {6432 + 3 * Brick_Length - 5, MAP_LAND}, {6432 + 4 * Brick_Length - 5, MAP_LAND},
			{6720 + Brick_Length-5, MAP_LAND}, {6720 + 2 * Brick_Length - 5, MAP_LAND}, {6720 + 3 * Brick_Length - 5, MAP_LAND}, {6720 + 4 * Brick_Length - 5, MAP_LAND},
			{7104 + Brick_Length-5, MAP_LAND}, {7104 + 2 * Brick_Length - 5, MAP_LAND}, {7104 + 3 * Brick_Length - 5, MAP_LAND}, {7104 + 5 * Brick_Length - 5, MAP_LAND},
			{7440 + Brick_Length-5, MAP_LAND}, {7440 + 2 * Brick_Length - 5, MAP_LAND}, {7440 + 3 * Brick_Length - 5, MAP_LAND}, {7440 + 4 * Brick_Length - 5, MAP_LAND},
			{8687 + Brick_Length-5, MAP_LAND}, {8687 + 2 * Brick_Length - 5, MAP_LAND}, {8687 + 3 * Brick_Length - 5, MAP_LAND}, {8687 + 4 * Brick_Length - 5, MAP_LAND}, {8687 + 5 * Brick_Length - 5, MAP_LAND},
				{8687 + 6 * Brick_Length-5, MAP_LAND}, {8687 + 7 * Brick_Length - 5, MAP_LAND}, {8687 + 9 * Brick_Length - 5, MAP_LAND},		//（上面的+了5，这里的-了5是为了收窄一点）
			{9504 + Brick_Length-5, MAP_LAND}}
	},

	{1,					//门
		{{9904, MAP_LAND - Door_Height}},
		{{9904 + Door_Lenght, MAP_LAND}}
	}
};


bool Obstacle::is_collide_left(const Collider& Mali, int& left_pos)		//Mario左边发生了碰撞（有接触）（引用是边界的位置（防止超出边界）)
{
	for (int i = 0; i < All_Kind; ++i)
		for (int j = 0; j < Brick[i].num; ++j)
			if (Mali.y + Mali.height > Brick[i].p1[j][1] && Mali.x <= Brick[i].p2[j][0] && Mali.x + Mali.length > Brick[i].p1[j][0])
			{
				left_pos = Brick[i].p2[j][0];
				return true;
			}
	return false;
}

bool Obstacle::is_collide_right(const Collider& Mali, int& right_pos)		//Mario右边发生了碰撞（有接触）
{
	for (int i = 0; i < All_Kind; ++i)
		for (int j = 0; j < Brick[i].num; ++j)
			if (Mali.y + Mali.height > Brick[i].p1[j][1] && Mali.x < Brick[i].p2[j][0] && Mali.x + Mali.length >= Brick[i].p1[j][0])
			{
				right_pos = Brick[i].p1[j][0];
				return true; 
			}
	return false;
}

bool Obstacle::is_collide_down(Collider& Mali, int& down_pos)		//Mario下面发生了碰撞（有接触）		(判断Mario是否掉下去死亡）
{
	for (int i = 0; i < All_Kind; ++i)
		for (int j = 0; j < Brick[i].num; ++j)
			if (Mali.x + Mali.length > Brick[i].p1[j][0] && Mali.x < Brick[i].p2[j][0] && Mali.y + Mali.height >= Brick[i].p1[j][1])
			{
				if (i == 0 && j == 2)				//去掉（改为在Mario中掉下太深就死亡）
				{
					Mali.state = false;
				}
				down_pos = Brick[i].p1[j][1];
				return true;
			}
	return false;
}