#ifndef _MARIO_H_
#define _MARIO_H_

#define Mario_Small_Length 64
#define Mario_Small_Height 64
#define Mario_Big_Length 64
#define Mario_Big_Height 128

#define Bullet_Length 24
#define Bullet_Height 24

#include <graphics.h>
#include "Collider.h"

class Mario : public Collider{
private:
	const int map_show_left = 50;		//当马里奥移动到最左边距离时地图跟着移动
	const int map_show_right = 300;		//				最右边
	void change_map();			//保持地图跟着人物移动
	
public:
	IMAGE img_stand[4][4];		//站着（左右）
	IMAGE img_walk[4][4];
	IMAGE img_jump[4][4];
	IMAGE img_squat[4][4];
	IMAGE img_dead[1][2];
	int vdead_max = 18;	int adead = 2;
	int is_stand = 1;				//五种状态
	int is_walk = 0;
	int is_jump = 0;	int stop_time = 0;	int walk_step = 0;	//行走的图片帧率
	int is_squat = 0;
	int is_death = 0;
	bool is_over = false;
	bool is_win = false;
	
	int direction = 2;			//左右方向（1左2右）
	int vx = 0;		int vx_max = 9;		int ax = 1;		//x方向速度和加速度（摩檫力的）
	int vy = 0;		int vy_max = 36;	int ay = 3;		//y方向速度和加速度（摩檫力的）

	int buffer = 0;				//增幅 1是蘑菇（变大)，2是星星（无敌），3是花朵（厨师子弹）		（只能存在一种状态）
	int buffer_time = 0;	const int buffer_alltime = 500;		//状态持续的时间
	int flash_time = 0;		//无敌时闪烁的时间


	int mci_jump_sound = 0;
	int mci_jump_times = 0;

	int mci_turn_sound = 0;
	int mci_turn_times = 0;

	int mci_hit_sound = 0;
	int mci_hit_times = 0;

	int mci_attack_sound = 0;
	int mci_attack_times = 0;

	int mci_magic_sound = 0;
	int mci_magic_times = 0;

	int mci_coin_sound = 0;
	int mci_coin_times = 0;

	int mci_flag_sound = 0;
	int mci_flag_times = 0;

	int mci_stomp_sound = 0;
	int mci_stomp_times = 0;


	void load_img();
	void init();				//初始化人物
	void put_img();

	void up_date();
	void music_update();

	void clear_manip();
	void dead_manip();
};


class Bullet : public Collider {			//操作都在Mario中一起操作（调用函数）
public:
	static const int all_num = 5;			//子弹总数量
	static int num;							//子弹当前发射数量

	int direction = 1;
	int vx = 0;		int vx_max = 15;
	int vy = 0;		int vy_max = 21;	 const int ay = 3;

	static void load_img();
	static void init();
	static void put_img();

	static void up_date();

	static void clear_manip();
};



extern Mario Mali;
extern Bullet Bl[Bullet::all_num];

#endif 
