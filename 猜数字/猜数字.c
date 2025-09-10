#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<time.h >
#include<windows.h>



	void menu()
	{
		printf("*****************************\n");
		printf("*****************************\n");
		printf("********  猜  数  字 ********\n");
		printf("********    1.游玩   ********\n");
		printf("********    0.退出   ********\n");
		printf("*****************************\n");
		printf("*****************************\n");

	}
	void game()
	{
		printf("请注意，你有1分钟的时间，请在1-100内猜出数字，否则电脑将会黑屏\n");
		//system("shutdown -s -t 60");
		int guess = 0;
		int ret = rand()%100+1; 
			
		while (1)
		{
			printf("请输入数字:>");
			scanf("%d", &guess);
		    if (guess < ret)
			{
				printf("猜小了\n");
			}
			else if (guess > ret)
			{
				printf("猜大了\n");
			}
			else if(guess == ret)
			{
				printf("恭喜你，猜对了\n\n");
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
			printf("请选择并回车:>");
			scanf("%d", &input);
			switch (input)
			{
			case 1:
				game();
				break;
	
			 case 0:
				printf("退出游戏\n");
				break;
			default:
				printf("\n选择错误，重新选择！\n");
				break;
			}
		} while (input);

	}
