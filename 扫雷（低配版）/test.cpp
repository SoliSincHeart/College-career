#include"game.h"

int main()
{
	//´°¿Ú
	initgraph(COL*IS,ROW*IS,0);
	//ÆåÅÌ
	int row = 0;
	int col = 0;
	int arr[ROW][COL] = { 0 };
	Make(arr);
	Calulation(arr);
	//Ö÷Ñ­»·
	while (true)
	{
		ExMessage msg;
		while (peekmessage(&msg, EX_MOUSE))
		{
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
			case WM_RBUTTONDOWN:
				Mouse(&msg, arr);
				Judge(arr, msg.x/IS, msg.y/IS);
				system("cls");
				break;
			}
			Draw(arr);
		}
	}
	Show(arr);

	getchar();
	return 0;
}


