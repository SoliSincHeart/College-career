#include"game.h"

IMAGE imgs[12];
int first = 0;
void loadResource()
{
	for (int i = 0;i < 12;i++)
	{
		char image[40] = { 0 };
		sprintf_s(image, "./images/%d.jpg", i);
		loadimage(&imgs[i], image, IS, IS);
	}
}


void Show(int arr[ROW][COL])
{
	for (int i = 0;i < ROW;i++)
	{
		for (int j = 0;j < COL;j++)
		{
			printf("%2d ", arr[i][j]);
		}
		printf("\n");
	}
}
void Make(int arr[ROW][COL])
{
	srand((unsigned)time(NULL));
	for (int i = 0;i < Mine;)
	{
		int r = rand() % (ROW - 1);
		int c = rand() % (COL - 1);
		if (arr[r][c] == 0)
		{
			arr[r][c] = -1;
			i++;
		}
	}
}

void Calulation(int arr[ROW][COL])
{
	//���������
	for (int m = 0;m < ROW; m++)
	{
		for (int n = 0;n < COL;n++)
		{
			if (arr[m][n] == -1)
			{
				for (int i = m - 1;i <= m + 1;i++)
				{
					for (int j = n - 1;j <= n + 1;j++)
					{
						if ((i >= 0 && i < ROW && j >= 0 && j < COL) && arr[i][j] != -1)
						{
							++arr[i][j];
						}
					}
				}
			}
		}
	}
	for (int i = 0;i < ROW;i++)
	{
		for (int j = 0;j < COL;j++)
		{
			arr[i][j] += 20;
		}
	}

}

void Init(int arr[ROW][COL],int row,int col)
{
	arr[row][col] = 20;
	for (int i = 0;i < ROW;i++)
	{
		for (int j = 0;j<COL;j++)
		{
			arr[i][j] -= 20;
		}
	}
	//�׵����λ��
	srand((unsigned)time(NULL));

	memset(arr, 0, sizeof(int) * ROW * COL);
	for (int i = 0;i < Mine;)
	{
		int r = rand() % (ROW-1);
		int c = rand() % (COL-1);
		if (arr[r][c] == 0)
		{
			arr[r][c] = -1;
			i++;
		}
	}

	//���������
	for (int m = 0;m < ROW; m++)
	{
		for (int n = 0;n < COL;n++)
		{
			if (arr[m][n] == -1)
			{
				for (int i = m - 1;i <= m + 1;i++)
				{
					for (int j = n - 1;j <= n + 1;j++)
					{
						if ((i >= 0 && i < ROW && j >= 0 && j < COL) && arr[i][j] != -1)
						{
							++arr[i][j];
						}
					}
				}
			}
		}
	}
	for (int i = 0;i < ROW;i++)
	{
		for (int j = 0;j < COL;j++)
		{
			arr[i][j] += 20;
		}
	}
}

void Draw(int arr[ROW][COL])
{
	loadResource();
	for (int i = 0;i < ROW;i++)
	{
		for (int j = 0;j < COL;j++)
		{
			if (arr[i][j] >= 0 && arr[i][j] <= 8)
			{
				putimage(j * IS, i * IS, &imgs[arr[i][j]]);
			}
			else if (arr[i][j] == -1)
			{
				putimage(j * IS, i * IS, &imgs[9]);
			}
			else if (arr[i][j] >= 19 && arr[i][j] <= 28)
			{
				putimage(j * IS, i * IS, &imgs[10]);
			}
			else if (arr[i][j] >= 39 && arr[i][j] < +48)
			{
				putimage(j * IS, i * IS, &imgs[11]);
			}
		}
	}
}

void Mouse(ExMessage* msg, int arr[ROW][COL])
{
	//��λ���λ��
	int c = msg->x / IS;
	int r = msg->y / IS;
	//�������
	if (msg->message == WM_LBUTTONDOWN)
	{
		first++;
		if (first == 1 && arr[r][c] == 19)
		{
			Init(arr,r,c);
		}
		if (arr[r][c] >= 19 && arr[r][c] <= 28)
		{
			
			PlaySound("./images/Lclick.wav", NULL, SND_ASYNC | SND_FILENAME);
			arr[r][c] -= 20;
			Blank(arr, r, c);
		}
	}
	//�Ҽ�����
	else if (msg->message == WM_RBUTTONDOWN)
	{
		if (arr[r][c] >= 19 && arr[r][c] <= 28)
		{
			PlaySound("./images/Rclick.wav", NULL, SND_ASYNC | SND_FILENAME);
			arr[r][c] += 20;
		}
		else if (arr[r][c] >= 39)
		{
			arr[r][c] -= 20;
		}
	}
}

void Blank(int arr[ROW][COL], int row, int col)
{
	if (arr[row][col] == 0)
	{
		for (int r = row - 1;r <= row + 1;r++)
		{
			for (int c = col - 1;c <= col + 1;c++)
			{
				if ((r >= 0 && r < ROW && c >= 0 && c < COL) && arr[r][c] >= 19 && arr[r][c] <= 28)
				{
					arr[r][c] -= 20;
					Blank(arr, r, c);
				}
			}
		}

	}
}

int Judge(int arr[ROW][COL], int col, int row)
{
	Draw(arr);

	//����
	if (arr[row][col] == -1)
	{
		Draw(arr);
		int s = MessageBox(GetHWnd(), "�˾Ͷ���������һ�Ρ�", "�����ˣ�", MB_OKCANCEL);
	    if (s == IDOK)
	    {
		  Init(arr,row,col);
	    }
     	else
	    {
		  exit(0);
	    }

	}
	//Ӯ��
	int count = 0;
	for (int i = 0;i < ROW;i++)
	{
		for (int j = 0;j < COL;j++)
		{
			if (arr[i][j] >= 0 && arr[i][j] <= 8)
			{
				++count;
			}
		}
	}
	if (ROW * COL - Mine == count)
	{
		Draw(arr);
		int s = MessageBox(GetHWnd(), "�ٽ�������", "��Ӯ�ˣ�", MB_OKCANCEL);
		if (s == IDOK)
		{
			Init(arr,row,col);
		}
		else
		{
			exit(0);
		}

	}
	//continue
	return 0;
}

