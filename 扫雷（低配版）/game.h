#pragma once
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<easyx.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

#define ROW 17//��
#define COL 17//��
#define Mine 30//�׵�����
#define IS 40//ͼƬ��С


//����
void Show(int arr[ROW][COL]);
//����
void Calulation(int arr[ROW][COL]);
//����
void Make(int arr[ROW][COL]);
//��ʼ���׵�����ֲ�
void Init(int arr[ROW][COL],int row,int col);
//��ͼ
void Draw(int arr[ROW][COL]);
//���ٿ�
void Mouse(ExMessage* msg, int arr[ROW][COL]);
//�����Ų�
void Blank(int arr[ROW][COL], int row, int col);
//��Ӯ����
int Judge(int arr[ROW][COL], int col, int row);



