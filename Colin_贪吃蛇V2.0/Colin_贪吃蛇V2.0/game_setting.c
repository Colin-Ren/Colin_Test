#include "game_setting.h"
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
int dos_layout[HIGH][WIDTH] = { 0 };  // ��ά�����¼����Ԫ�� 
//-2��ʾʳ�-1��ʾ�߿� 0��ʾ�ո� 1��ʾ��ͷ�� ����1��ʾ����
int food_x = 0, food_y = 0;  // ʳ�������
int move_to = 0;  // �ƶ����� 1 = �ϣ� 2 = �£� 3 = �� 4 = ��
// �ƶ�dos���λ��
void goto_xy(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(handle, coord);
}

// ��ʼ����Ϸ����
void init_game()
{
	//goto_xy(20, 0);

	// ��ʼ�����ֽ����ֵ
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

	// ��ʼ��ͷ��λ��
	dos_layout[HIGH / 2][WIDTH / 2] = 1;
	// ��ʼ�����λ��
	for (int i = 1; i < SNAKE_LEN; i++)
	{
		dos_layout[HIGH / 2][WIDTH / 2 - i] = 1 + i;
	}
	
	// ��ʼʳ���λ��
	food_x = rand() % (HIGH - 2) + 1;
	food_y = rand() % (WIDTH - 2) + 1;
	dos_layout[food_x][food_y] = -2;

	move_to = 4;  // С�߳�ʼ�����ƶ�
}

// ��ӡ��Ϸ����
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

//�������ع�꺯��
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = FALSE;
	cursor.dwSize = sizeof(cursor);
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(handle, &cursor);
}

// �����û�����
void player_input()
{
	if (_kbhit())
	{
		char my_ch = 0;  // �����û������ַ�
		my_ch = _getch();  // 72 77 80 75 �� �� �� ��
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

// С���ƶ��ж�
void move_snake()
{
	int max = 0;
	int new_head_i = 0, new_head_j = 0;  // �ƶ�����ͷ��λ��
	int old_head_i = 0, old_head_j = 0;  // �ƶ�����ͷ��λ��
	int old_tail_i = 0, old_tail_j = 0;  // �ƶ�ǰβ�͵�λ��

	for (int i = 1; i < HIGH - 1; i++)
	{
		for (int j = 1; j < WIDTH - 1; j++)
		{
			if (dos_layout[i][j] > 0)
			{
				dos_layout[i][j]++;  // ����+1
			}
			if (2 == dos_layout[i][j])
			{
				// ��¼�ƶ�ǰͷ��λ��
				old_head_i = i;
				old_head_j = j;
			}
			if (max < dos_layout[i][j])
			{
				// ��¼�ƶ�ǰβ�͵�λ��
				max = dos_layout[i][j];
				old_tail_i = i;
				old_tail_j = j;
			}
		}
	}
	switch (move_to)
	{
	case 1:
		new_head_i = old_head_i - 1;  // ȷ������ͷλ��
		new_head_j = old_head_j;
		break;
	case 2:
		new_head_i = old_head_i + 1;  // ȷ������ͷλ��
		new_head_j = old_head_j;
		break;
	case 3:
		new_head_i = old_head_i;  // ȷ������ͷλ��
		new_head_j = old_head_j - 1;
		break;
	case 4:
		new_head_i = old_head_i;  // ȷ������ͷλ��
		new_head_j = old_head_j + 1;
		break;
	}

	// �ж�����ͷ�Ƿ�Ե�ʳ��
	if (new_head_i == food_x && new_head_j == food_y)
	{
		// ��ʼʳ���λ��
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
	
	// �ж���Ϸ���� ��ͷײ���߿� �� ��ͷײ������
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