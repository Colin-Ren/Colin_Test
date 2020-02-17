#pragma once
#define HIGH 20   // 界面边框高
#define WIDTH 80  // 界面边框宽 30 * 120
#define SNAKE_LEN 10  // 初始蛇身长度
// 初始化游戏数据
void init_game();

// 移动dos光标位置
void goto_xy(int x, int y);

// 打印游戏界面
void show();

// 定义隐藏光标函数
void HideCursor();

// 接受用户输入
void player_input();

// 小蛇移动判断
void move_snake();