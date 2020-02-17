/*********************************************************************************************
*									作者：Colin												 *
*						曾经，我写的代码只有我和上帝知道是什么意思								 *							 *
*								 现在，只有上帝知道。											 *				 *
*								 o															 *
*								  o															 *
*								   o														 *
*									 ^__^													 *
*									 (oo)\_______											 *
*									 (__)\       )\ / \										 *
*										 || ----w |											 *
*										 ||      ||											 *
**********************************************************************************************/
#if 1
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_setting.h"
#include <time.h>

int main(int argc, char *argv[])
{
	system("color 2");
	system("title 黑马");
	HideCursor();
	init_game();
	while (1)
	{
		show();
		player_input();
		//move_snake();
	}
	system("pause");
	return 0;
}
#endif