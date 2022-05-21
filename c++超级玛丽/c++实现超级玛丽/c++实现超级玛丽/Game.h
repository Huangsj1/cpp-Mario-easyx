#ifndef _GAME_H_
#define _GAME_H_

class Game {
public:
	bool start = false;		//游戏是否开始
	bool pause = false;		//游戏暂停
	bool over = false;		//游戏结束

	int player = 1;			//玩家数量
	int score = 0;

	void clear_data();

	void start_game();
	void play_game();
	void continue_game();
	void game_over();
	void game_win();
};



#endif