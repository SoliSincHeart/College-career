#pragma once
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<easyx.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

#define ROW 17//行
#define COL 17//列
#define Mine 30//雷的数量
#define IS 40//图片大小


//棋盘
void Show(int arr[ROW][COL]);
//计算
void Calulation(int arr[ROW][COL]);
//设雷
void Make(int arr[ROW][COL]);
//初始化雷的随机分布
void Init(int arr[ROW][COL],int row,int col);
//贴图
void Draw(int arr[ROW][COL]);
//鼠标操控
void Mouse(ExMessage* msg, int arr[ROW][COL]);
//连环排查
void Blank(int arr[ROW][COL], int row, int col);
//输赢条件
int Judge(int arr[ROW][COL], int col, int row);



