#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<time.h >
#include<windows.h>



	void menu()
	{
		printf("*****************************\n");
		printf("*****************************\n");
		printf("********  ��  ��  �� ********\n");
		printf("********    1.����   ********\n");
		printf("********    0.�˳�   ********\n");
		printf("*****************************\n");
		printf("*****************************\n");

	}
	void game()
	{
		printf("��ע�⣬����1���ӵ�ʱ�䣬����1-100�ڲ³����֣�������Խ������\n");
		//system("shutdown -s -t 60");
		int guess = 0;
		int ret = rand()%100+1; 
			
		while (1)
		{
			printf("����������:>");
			scanf("%d", &guess);
		    if (guess < ret)
			{
				printf("��С��\n");
			}
			else if (guess > ret)
			{
				printf("�´���\n");
			}
			else if(guess == ret)
			{
				printf("��ϲ�㣬�¶���\n\n");
				system("shutdown -a");
				break;
			}

	    }
		
	
	}
	int main()
	{
		int input = 0;
		srand((unsigned int)time(NULL));

		do
		{
			menu();
			printf("��ѡ�񲢻س�:>");
			scanf("%d", &input);
			switch (input)
			{
			case 1:
				game();
				break;
	
			 case 0:
				printf("�˳���Ϸ\n");
				break;
			default:
				printf("\nѡ���������ѡ��\n");
				break;
			}
		} while (input);

	}
