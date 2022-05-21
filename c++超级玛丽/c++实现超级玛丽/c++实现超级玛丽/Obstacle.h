//补充小怪也碰到这些东西后反弹

#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

#include "Collider.h"
#include "Mario.h"

#define Pipe_Height_1 97
#define Pipe_Height_2 145
#define Pipe_Height_3 193
#define Pipe_Lenght   95

#define Brick_Height  48
#define Brick_Length  48

#define Door_Height   201
#define Door_Lenght   101

class Obstacle{
public:
	static const int All_Kind = 5;		//所有种类的障碍物（未加上头顶的砖块）
	int num = 0;		//每种障碍物的数量
	int p1[30][2];			//左上角坐标
	int p2[30][2];			//右下角坐标

	static bool is_collide_left(const Collider& Mali, int& left_pos);
	static bool is_collide_right(const Collider& Mali, int& right_pos);
	static bool is_collide_down(Collider& Mali, int& down_pos);			//若碰到底部，马里奥就死亡，所以不能为const
};

#endif

