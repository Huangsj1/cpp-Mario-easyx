#include "Bkground.h"

Bkground Map;		//定义一个变量放在.cpp最后面（其他文件中使用要用extern+类型名+变量名）（只能在.cpp中定义，若在.h中定义，会出现定义两次的错误）

void Bkground::bk_move(int xm)		//窗口左右移动（有边界限制）
{
	if (x + xm >= 0 && x + xm <= length - WD_LENGTH - MAP_EXTRA)
		x += xm;
}

void Bkground::load_img()		//加载图片
{
	loadimage(&img, "E:\\小游戏\\c++超级玛丽\\c++实现超级玛丽\\c++实现超级玛丽\\pictures\\BkGround\\level_1.png", length, height);
}

void Bkground::put_img()		//放置图片
{
	putimage(0, 0, WD_LENGTH, WD_HEIGHT, &img, x, y);
}


void Bkground::clear_manip()
{
	x = 0;
	y = 0;
}