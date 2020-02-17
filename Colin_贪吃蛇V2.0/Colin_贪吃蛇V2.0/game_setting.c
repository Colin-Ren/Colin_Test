#include "game_setting.h"
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
int dos_layout[HIGH][WIDTH] = { 0 };  // 二维数组记录布局元素 
//-2表示食物，-1表示边框， 0表示空格， 1表示蛇头， 大于1表示身体
int food_x = 0, food_y = 0;  // 食物的坐标
int move_to = 0;  // 移动方向 1 = 上， 2 = 下， 3 = 左， 4 = 右
// 移动dos光标位置
void goto_xy(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(handle, coord);
}

// 初始化游戏数据
void init_game()
{
	//goto_xy(20, 0);

	// 初始化布局界面的值
	for (int i = 0; i < HIGH; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (0 == i)
			{
				dos_layout[i][j] = -1;
			}
			else if (i == HIGH - 1)
			{
				dos_layout[i][j] = -1;
			}
			else
			{
				dos_layout[i][0] = -1;
				dos_layout[i][WIDTH - 1] = -1;
			}
		}
	}

	// 初始蛇头的位置
	dos_layout[HIGH / 2][WIDTH / 2] = 1;
	// 初始蛇身的位置
	for (int i = 1; i < SNAKE_LEN; i++)
	{
		dos_layout[HIGH / 2][WIDTH / 2 - i] = 1 + i;
	}
	
	// 初始食物的位置
	food_x = rand() % (HIGH - 2) + 1;
	food_y = rand() % (WIDTH - 2) + 1;
	dos_layout[food_x][food_y] = -2;

	move_to = 4;  // 小蛇初始往右移动
}

// 打印游戏界面
void show()
{	
	for (int i = 0; i < HIGH; i++)
	{
		goto_xy(20, i);
		
		for (int j = 0; j < WIDTH; j++)
		{
			if (0 == dos_layout[i][j])
			{
				printf(" ");
			}
			else if (-1 == dos_layout[i][j])
			{
				printf("*");
			}
			else if (1 == dos_layout[i][j])
			{
				printf("@");
			}
			else if (dos_layout[i][j] > 1)
			{
				printf("O");
			}
			else if (-2 == dos_layout[i][j])
			{
				printf("f");
			}
		}
		printf("\n");
	}
	Sleep(50);
}

//定义隐藏光标函数
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = FALSE;
	cursor.dwSize = sizeof(cursor);
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(handle, &cursor);
}

// 接受用户输入
void player_input()
{
	if (_kbhit())
	{
		char my_ch = 0;  // 接收用户输入字符
		my_ch = _getch();  // 72 77 80 75 上 右 下 左
		if (my_ch == 'w' || my_ch == 'W' || my_ch == 72)
		{
			if (move_to != 2)
			{
				move_to = 1;
				move_snake();
				return;
			}
		}
		else if (my_ch == 'd' || my_ch == 'D' || my_ch == 77)
		{
			if (move_to != 3)
			{
				move_to = 4;
				move_snake();
				return;
			}
		}
		else if (my_ch == 's' || my_ch == 'S' || my_ch == 80)
		{
			if (move_to != 1)
			{
				move_to = 2;
				move_snake();
				return;
			}
		}
		else if (my_ch == 'a' || my_ch == 'A' || my_ch == 75)
		{
			if (move_to != 4)
			{
				move_to = 3;
				move_snake();
				return;
			}
		}
	}
	move_snake();
}

// 小蛇移动判断
void move_snake()
{
	int max = 0;
	int new_head_i = 0, new_head_j = 0;  // 移动后蛇头的位置
	int old_head_i = 0, old_head_j = 0;  // 移动后蛇头的位置
	int old_tail_i = 0, old_tail_j = 0;  // 移动前尾巴的位置

	for (int i = 1; i < HIGH - 1; i++)
	{
		for (int j = 1; j < WIDTH - 1; j++)
		{
			if (dos_layout[i][j] > 0)
			{
				dos_layout[i][j]++;  // 正数+1
			}
			if (2 == dos_layout[i][j])
			{
				// 记录移动前头部位置
				old_head_i = i;
				old_head_j = j;
			}
			if (max < dos_layout[i][j])
			{
				// 记录移动前尾巴的位置
				max = dos_layout[i][j];
				old_tail_i = i;
				old_tail_j = j;
			}
		}
	}
	switch (move_to)
	{
	case 1:
		new_head_i = old_head_i - 1;  // 确定新蛇头位置
		new_head_j = old_head_j;
		break;
	case 2:
		new_head_i = old_head_i + 1;  // 确定新蛇头位置
		new_head_j = old_head_j;
		break;
	case 3:
		new_head_i = old_head_i;  // 确定新蛇头位置
		new_head_j = old_head_j - 1;
		break;
	case 4:
		new_head_i = old_head_i;  // 确定新蛇头位置
		new_head_j = old_head_j + 1;
		break;
	}

	// 判断新蛇头是否吃到食物
	if (new_head_i == food_x && new_head_j == food_y)
	{
		// 初始食物的位置
		while (1)
		{
			food_x = rand() % (HIGH - 2) + 1;
			food_y = rand() % (WIDTH - 2) + 1;
			if (dos_layout[food_x][food_y] < 1)
			{
				break;
			}
		}
		
		dos_layout[food_x][food_y] = -2;
	}
	else
	{
		dos_layout[old_tail_i][old_tail_j] = 0;
	}
	
	// 判断游戏结束 蛇头撞到边框 或 蛇头撞到蛇身
	if (-1 == dos_layout[new_head_i][new_head_j] || dos_layout[new_head_i][new_head_j] > 1)
	{
		//dos_layout[new_head_i][new_head_j] = 1;
		//show();
		printf("Game Over!\n");
		Sleep(5000);
		exit(0);
	}
	dos_layout[new_head_i][new_head_j] = 1;
}