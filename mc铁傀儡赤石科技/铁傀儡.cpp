#include<iostream>
#include<windows.h>
using namespace std;
class Shuttechnology
{
public:
	void Shut1()
	{
		cout << "  囧  " << endl;
		cout << "□ 口□" << endl;
		cout << "  口 " << endl;
	}

	void Shut2()
	{
		cout << "  囧  " << endl;
		cout << "口□ 口" << endl;
		cout << "  □ " << endl;
	}
};

int main()
{
	Shuttechnology shut;

	while (1)
	{
		Sleep(500);
		system("cls");
		shut.Shut1();
		Sleep(500);
		system("cls");
		shut.Shut2();
	}
	return 0;
}
