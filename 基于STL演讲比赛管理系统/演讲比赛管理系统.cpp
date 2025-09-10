#include<iostream>
#include"SpeechManager.h"
using namespace std;

int main()
{
	srand((unsigned int)time(NULL));
	SpeechManager sm;

	char choice = 0;
	while (true)
	{
		sm.show_Menu();
		cout << "ÇëÑ¡Ôñ£º";
		cin >> choice;
		switch (choice)
		{
		case '1':
			sm.startSpeech();
			break;
		case '2':
			sm.showRecord();
			break;
		case '3':
			sm.clearRecord();
			break;
		case '0':
			sm.exitSystem();
			break;
		default:
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}