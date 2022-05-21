#ifndef _COLLIDER_H_
#define _COLLIDER_H_

class Collider {			//碰撞体（其他人物，障碍物的基类）
public:
	int x = 0;			//左上角坐标（总地图）
	int y = 0;			
	int length = 0;
	int height = 0;
	bool state = false;	//是否存在
	
	Collider(int x1 = 0, int y1 = 0, int len = 0, int hei = 0, int sta = false) : x(x1), y(y1), length(len), height(hei), state(sta) {}

	virtual void init() {}		//load_img存在于init中
	virtual void load_img() {}
	virtual void put_img() {}	

	virtual void up_date() {}	

	bool is_collide(const Collider& o)		//判断是否碰撞
	{
		bool x_ = x + length / 2 >= o.x - o.length / 2 && x - length / 2 <= o.x + o.length / 2;		//左右边界碰撞
		bool y_ = y + height / 2 >= o.y - o.height / 2 && y - height / 2 <= o.y - o.height / 2;		//上下边界碰撞
		return x && y;
	}

};

#endif

