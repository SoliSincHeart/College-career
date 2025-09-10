#pragma once

#include <stdio.h>
#include<stdlib.h>
#include <time.h>

#define ROW 3
#define COL 3


void InitBoard(char board[ROW][COL], int row, int col);

void DisplayBoard(char board[ROW][COL], int row, int col);

void PlayerMore(char board[ROW][COL], int row, int col);

void ComputerMore(char board[ROW][COL], int row, int col);

char Win(char board[ROW][COL], int row, int col);