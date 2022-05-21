#ifndef _ENEMIES_H_
#define _ENEMIES_H_

#define PI 3.14159265
#define Goomba_Length 48
#define Tortoise_Length 48
#define Tortoise_Height_1 72
#define Tortoise_Height_2 42
#define Piranha_Length 48
#define Piranha_Height 72

#include "Collider.h"

class Goomba : public Collider {
public:
	static const int all_num = 11;
	int xl;		//运动最左边
	int xr;		//最右边
	int direction = 1;		//1向左，2向右
	int vx = -3;		//匀速运动
	int vy = 0;		const int ay = 3;
	bool is_attack = false;			//是否被攻击（被攻击后弹开死亡）
	int stop_time = 0;
	int dead_showtime = 25;

	Goomba(int x1 = 0, int y1 = 0, int len = 0, int hei = 0, bool sta = false, int xl_ = 0, int xr_ = 0) : Collider(x1, y1, len, hei, sta), xl(xl_), xr(xr_){}

	static void load_img();
	static void put_img();

	static bool touch(const Collider& Mario, bool& trample, bool is_attack);			//是否踩踏，是否被攻击
	static void up_date();
	
	static void clear_manip();
};


class Tortoise : public Collider {
public:
	static const int all_num = 3;
	int xl;
	int xr;
	int direction = 1;
	int vx = -3;	const int vx_fast = 9;
	int vy = 0;		const int ay = 3;
	int form = 1;		//形态（1是正常，2是龟壳）
	int step_time = 0;
	int walk_step = 0;
	bool is_attack = false;
	int stop_time = 0;

	Tortoise(int x1 = 0, int y1 = 0, int len = 0, int hei = 0, bool sta = false, int xl_ = 0, int xr_ = 0) : Collider(x1, y1, len, hei, sta), xl(xl_), xr(xr_){}

	static void load_img();

	static void put_img();

	static bool touch(const Collider& Mario, bool& trample, bool is_attack);
	static void up_date();

	static void clear_manip();
};


class Piranha : public Collider{
public:
	static const int all_num = 3;
	int direction = 1;			//1是向上，2是向下（当向下到达0时，变为负值，停止，不断++，直到变为1再向上）
	int vy = 1;		
	int y_show = 0;				//露出来的长度（每次增加height/4，当到达顶峰时，改变direction，减少show）
	int walk_step = 0;
	int step_time = 0;			//切换动作的时间（当达到一定次数时才切换动作）
	int vx = 0;	
	const int ay = 3;
	bool is_attack = false;
	int stop_time = 0;

	Piranha(int x1 = 0, int y1 = 0, int len = 0, int hei = 0, bool sta = true) : Collider(x1, y1, len, hei, sta) {}

	static void load_img();

	static void put_img();

	static bool touch(const Collider& Mario, bool& trample, bool is_attack);
	static void up_date();

	static void clear_manip();
};

#endif