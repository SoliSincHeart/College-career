#define _CRT_SECURE_NO_WARNINGS

#include "game.h"


void menu()
{
	printf("\n");
	printf("******************************\n");
	printf("*********  �� �� ��  *********\n");
	printf("*****   1.����  0.�˳�   *****\n");
	printf("******************************\n");
	printf("\n");

}

void game()
{
	char ret = 0;
	char board[ROW][COL] = {0};

	printf("�����Ͻ�Ϊ������ꡰ1 1��,���к���\n");

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
		printf("\n\n<<���Ӯ>>\n");
	}
	else if(ret == '#')
	{
		printf("\n\n<<����Ӯ>>\n");
	}
	else
	{
		printf("\n\n<<ƽ��>>\n");
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
		printf("��ѡ�񲢻س�:>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			printf("\n");
			game();
			break;
		case 0:
			printf("\n");
			printf("�˳���Ϸ\n");
			break;
		default:
			printf("\n");
			printf("ѡ�����\n");
			break;
		}
	} while (input);

	return 0;
}