#pragma once
#define HIGH 20   // ����߿��
#define WIDTH 80  // ����߿�� 30 * 120
#define SNAKE_LEN 10  // ��ʼ������
// ��ʼ����Ϸ����
void init_game();

// �ƶ�dos���λ��
void goto_xy(int x, int y);

// ��ӡ��Ϸ����
void show();

// �������ع�꺯��
void HideCursor();

// �����û�����
void player_input();

// С���ƶ��ж�
void move_snake();