#define _CRT_SECURE_NO_WARNINGS

#include "game.h"


void menu()
{
	printf("\n");
	printf("******************************\n");
	printf("*********  三 子 棋  *********\n");
	printf("*****   1.游玩  0.退出   *****\n");
	printf("******************************\n");
	printf("\n");

}

void game()
{
	char ret = 0;
	char board[ROW][COL] = {0};

	printf("以左上角为起点坐标“1 1”,先行后列\n");

	InitBoard(board, ROW, COL);
	DispalyBoard(board, ROW, COL);

	while (1)
	{
		PlayerMore(board,ROW,COL);
		ret = Win(board, ROW, COL);
		if (ret != 'C')
		{
			break;
		}
		DispalyBoard(board, ROW, COL);


		ComputerMore(board,ROW,COL);
		ret = Win(board, ROW, COL);
		if (ret != 'C')
		{
			break;
		}
		DispalyBoard(board, ROW, COL);

	}
	if (ret == '*')
	{
		printf("\n\n<<玩家赢>>\n");
	}
	else if(ret == '#')
	{
		printf("\n\n<<电脑赢>>\n");
	}
	else
	{
		printf("\n\n<<平局>>\n");
	}
	DispalyBoard(board, ROW, COL);

}

int main()
{
	srand((unsigned int)time(NULL));
	int input = 0;
	do
	{
		menu();
		printf("请选择并回车:>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			printf("\n");
			game();
			break;
		case 0:
			printf("\n");
			printf("退出游戏\n");
			break;
		default:
			printf("\n");
			printf("选择错误！\n");
			break;
		}
	} while (input);

	return 0;
}