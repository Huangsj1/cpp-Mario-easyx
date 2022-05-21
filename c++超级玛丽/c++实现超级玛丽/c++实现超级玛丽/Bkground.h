#ifndef _BKGROUND_H_
#define _BKGROUND_H_

#include <graphics.h>

//以整幅地图为坐标，显示的只是部分地图
#define WD_LENGTH 900		//图形界面窗口的长度
#define WD_HEIGHT 672		//图形界面窗口的宽度
#define MAP_EXTRA 906		//地图右边多出的部分
#define MAP_LAND 600		//地图地面到顶的距离

class Bkground {
public:
	int x = 0;					//当前背景所要放置的坐标（相对于整张地图）
	int y = 0;
	const int length = 11076;
	const int height = 672;
	IMAGE img;

	void bk_move(int xm);		//窗口左右移动

	void load_img();			//加载图片
	void put_img();				//放置图片


	void clear_manip();
};

extern Bkground Map;

#endif