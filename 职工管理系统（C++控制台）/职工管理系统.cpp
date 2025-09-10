#include<iostream>
#include<string>
using namespace std;
#include"WorkerManager.h"

#include"worker.h"
#include"employee.h"
#include"boss.h"
#include"manager.h"


int main()
{


	WorkerManager wm;
	char choice;

	while (true)
	{
		wm.Show_Menu();

		cout << "\nÇëÊäÈëÑ¡Ïî£º";
		cin >> choice;
		switch (choice)
		{
		case '0':
			wm.ExitSystem();
		case '1':
			wm.Add_Emp();
			break;
		case '2':
			wm.Show_Emp();
			break;
		case '3':
			wm.Del_Emp();
			break;
		case '4':
			wm.Mod_Emp();
			break;
		case '5':
			wm.Find_Emp();
			break;
		case '6':
			wm.Sort_Emp();
			break;
		case '7':
			break;
		default:
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}