#define _CRT_SECURE_NO_WARNINGS
#include "game.h"


void InitBoard(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0;i < row;i++)
	{
		for (j = 0;j < col;j++)
		{
		    board[i][j] = ' ';
		}
	}
}

void DispalyBoard(char board[ROW][COL], int row, int col)
{
	int i = 0;
	for (i = 0;i < row;i++)
	{
		int j = 0;

		for (j = 0;j < col;j++)
		{
			printf(" %c ", board[i][j]);
			if (j < col - 1)
				printf("|");
		}
		printf("\n");
		if (i < row - 1)
		{
			int j = 0;
			for (j = 0;j < col;j++)
			{
				printf("---");
				if (j < col - 1)
			         printf("|");
			}
			printf("\n");
		}
	}
}


void PlayerMore(char board[ROW][COL], int row, int col)
{
	int x = 0;
	int y = 0;
	printf("\n\n玩家下棋:>\n");


	while(1)
	{
		printf("请输入坐标(坐标数字以空格隔开):>");
		scanf("%d %d", &x, &y);
		if (x >= 1 && x <= row && y >= 1 && y <= col)
		{
			if (board[x - 1][y - 1] == ' ')
			{
				board[x - 1][y - 1] = '*';
				break;
			}
			else
			{
				printf("坐标被占用，请重新选择\n");
			}
		}
		else
		{
			printf("坐标非法，请重新输入\n");
		}
	}
}


void ComputerMore(char board[ROW][COL], int row, int col)
{
	printf("\n电脑下棋:>\n");
	int x = 0;
	int y = 0;

	while (1)
	{
		x = rand() % row;
		y = rand() % row;
		if (board[x][y] == ' ')
		{
			board[x][y] = '#';
			break;
		}
	}
}


int Full(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row;i++)
	{
		for (j = 0;j < col;j++)
		{
			if (board[i][j] == ' ')
				return 0;
		}
	}
}

char Win(char board[ROW][COL], int row, int col)
{
	int l = 0;
	for (l = 0;l < row;l++)
	{
		if (board[l][0] == board[l][1] && board[l][1] == board[l][2] && board[l][1] != ' ')
		{
			return board[l][1];
		}
	}


	int j = 0;
	for (j = 0;j < col;j++)
	{
		if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[1][j] != ' ')
		{
			return board[1][j];
		}
	}

	if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[1][1] != ' ')
	{
		return board[1][1];
	}

	if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[1][1] != ' ')
	{
		return board[1][1];
	}

	if (Full(board, row, col))
	{
		return 'Q';
	}

	return 'C';
}