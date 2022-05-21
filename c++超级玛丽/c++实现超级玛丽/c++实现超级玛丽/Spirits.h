#ifndef _SIPIRITS_H_
#define _SIPIRITS_H_

#define Brick_Length 48
#define Sepcial_Brick_Length 192
#define Coin_Length 48
#define Pole_Length 4
#define Pole_Height 370
#define Flag_Length 48

#include "Collider.h"
#include "Mario.h"

//---------------------------------------------------------- 普通砖块（固定住的） ----------------------------------------------------------------------------
class Com_Brick : public Collider {
public:
	static const int all_num = 29;
	
	Com_Brick(int x1 = 0, int y1 = 0, int len = 0, int hei = 0, int sta = false) : Collider(x1, y1, len, hei, sta){}

	static void init();
	static void load_img();
	static void put_img();

	static bool is_collide_left(const Collider& o, int& up_pos);
	static bool is_collide_right(const Collider& o, int& up_pos);
	static bool is_collide_up(const Collider& o, int& up_pos);
	static bool is_collide_down(const Collider& o, int& up_pos);
};


//---------------------------------------------------------- 特殊砖块 ------------------------------------------------------------------------------------
class Spe_Brick : public Collider {			//都是以条纹为基础的
public:
	static const int all_num = 12;
	int trigger = 1;		//是否触发（触发后就变成花纹砖块了）
	int kind = 0;				//0是没有东西，1是金币，2是蘑菇，3是星星，4是花朵
	int spnum = 0;			//特殊物品的数目
	int place = 0;			//特殊砖块是四个一组的，要将其拆分开（为了移动方便）
	int coltime = 0;		static const int clotime_max = 3;		//当碰撞次数超过最大时破碎
	int is_jump = 0;		//是否处于跳跃状态（问号砖块不会跳，产生的物品会跳）
	int vy = 0;				static const int vy_max = 10;		 static const int ay = 5;		//被碰撞时速度（与Mali加速度相同）
	int y_move = 0;			//运动的相对位移

	Spe_Brick(int x1 = 0, int y1 = 0, int len = 0, int hei = 0, int sta = false, int t = 1, int k = 0, int sn = 0, int p = 0, int ct = 0, int v = 0)
		: Collider(x1, y1, len, hei, sta), trigger(t), kind(k), spnum(sn), place(p) {}

	static void init();
	static void load_img();
	static void put_img();

	static bool is_collide_left(const Collider& o, int& up_pos);
	static bool is_collide_right(const Collider& o, int& up_pos);
	static bool is_collide_up(const Collider& o, int& up_pos);
	static bool is_collide_down(const Collider& o, int& up_pos);

	static void eat(Mario& Mali);			//Mario中调用

	static void clear_manip();
};



class Coin : public Collider {
public:
	static const int all_num = 8;
	int place = 0;

	Coin(int x1 = 0, int y1 = 0, int len = 0, int hei = 0, int sta = false, int pl = 0) : Collider(x1, y1, len, hei, sta), place(pl) {}

	static void init();
	static void load_img();
	static void put_img();

	static void eat(Mario& Mali);

	static void clear_manip();
};



class Flag : public Collider {
public:
	static const int all_num = 1;
	static const int vy = 8;
	int y_ground;
	bool touch = false;

	Flag(int x1 = 0, int y1 = 0, int len = 0, int hei = 0, int sta = true, int yg = 0, bool tou = false) : Collider(x1, y1, len, hei, sta), y_ground(yg), touch(tou) {}

	static void init();
	static void load_img();
	static void put_img();

	static bool is_touch(Mario& Mali);
	
	static void clear_manip();
};


extern Com_Brick Combrick[Com_Brick::all_num];
extern Spe_Brick Spebrick[Spe_Brick::all_num];


#endif

