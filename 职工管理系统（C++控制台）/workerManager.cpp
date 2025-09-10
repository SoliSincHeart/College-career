#include"workerManager.h"

WorkerManager::WorkerManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ������ڣ�" << endl;

		this->m_EmpNum = 0;
		this->m_EmpArray = nullptr;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout<<"�ļ�Ϊ�գ�"<<endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = nullptr;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	int num  = this->get_EmpNum();

	//cout<<"ְ������Ϊ��"<<num<<endl;

	this->m_EmpNum = num;
	this->m_EmpArray = new Worker*[this->m_EmpNum];
	this->init_Emp();
}

void WorkerManager::Show_Menu()
{
	cout << "*********************************" << endl;
	cout << "*****��ӭʹ��ְ������ϵͳ��******" << endl;
	cout << "********0.�˳�����ϵͳ***********" << endl;
	cout << "********1.����ְ����Ϣ***********" << endl;
	cout << "********2.��ʾְ����Ϣ***********" << endl;
	cout << "********3.ɾ����ְְ��***********" << endl;
	cout << "********4.�޸�ְ����Ϣ***********" << endl;
	cout << "********5.��ѯְ����Ϣ***********" << endl;
	cout << "********6.���ձ������***********" << endl;
	cout << "********7.���������Ϣ***********" << endl;
	cout << "*********************************" << endl;
}

void WorkerManager::ExitSystem()
{
	cout<<"��ӭ�´�ʹ�ã�"<<endl;
	system("pause");
	exit(0);
}


void WorkerManager::Add_Emp()
{
	cout << "���������ְ��������" << endl;

	int addNum = 0;

	cin>>addNum;
	if (addNum > 0)
	{
		int newSize = m_EmpNum + addNum;
		Worker** newSpace = new Worker*[newSize];

		if (!newSpace) {
			cout << "�ڴ����ʧ�ܣ�" << endl;
			return;
		}

		if (this->m_EmpArray!= nullptr)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}

		}

		for (int i = 0; i < addNum; i++)
		{
			int id; 
			string name;
			int dSelect;

			cout << "�������" << i + 1 << "��ְ���ı�ţ�";
			cin >> id;
			cout << "\n�������" << i + 1 << "��ְ����������";
			cin >> name;
			cout << "\n��ѡ���ְ���Ĳ��ű�ţ�\n" << endl;
			cout << "1.��ְͨ��\n2.����\n3.�ϰ�" << endl;
			cin >> dSelect;

			Worker* worker = nullptr;
			switch (dSelect)
			{
			case  1:
				worker = new Employee(id, name, 1);
				break;
			case  2:
				worker = new Manager(id, name, 2);
				break;
			case  3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}
			newSpace[this->m_EmpNum + i ] = worker;

		}
		delete[] this->m_EmpArray;

		this->m_EmpArray = newSpace;
		this->m_EmpNum  = newSize;
		this->m_FileIsEmpty = false;
		cout << "��ӳɹ���" <<addNum<<"����ְ����" << endl;

		this->save();
	}
	else
	{
		cout << "��������" << endl;
	}
	system("pause");
	system("cls");
}



void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}
	ofs.close();
}


int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int did;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> did)
	{
		num++;
	}
	return num;
}

void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int did;

	int index = 0;

	while (ifs >> id && ifs >> name && ifs >> did)
	{
		Worker* worker = NULL;

		if (did == 1)
		{
			worker = new Employee(id, name, did);
		}
		else if (did == 2)
		{
			worker = new Manager(id, name, did);
		}
		else if(did == 3)
		{
			worker = new Boss(id, name, did);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
	ifs.close();
}


void WorkerManager::Show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ�Ϊ�ջ򲻴��ڣ�" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout<<"�ļ�Ϊ�ջ򲻴��ڣ�"<<endl;
	}	
	else
	{
		cout << "������Ҫɾ����ְ����ţ�" ;
		int id;
		cin >> id; 

		int index = this->IsExist(id);
		if (index != -1)
		{
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;
			cout << "ɾ���ɹ���" << endl;
			this->save();
		}
		else
		{
			cout << "�����ڸ�ְ��" << endl;
		}
	}

	system("pause");
	system("cls");
}

int WorkerManager::IsExist(int id)
{
	int index = 0;

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			index = i;

			break;
		}
	}
	return index;
}

void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout<<"�ļ�Ϊ�ջ򲻴��ڣ�"<<endl;
	}
	else
	{
		cout << "������Ҫ�޸ĵ�ְ����ţ�";
		int id;
		cin >> id;

		int index = this->IsExist(id);

		if (index != -1)
		{
			delete this->m_EmpArray[index];

			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout << "�鵽��" << id << "��ְ����Ϣ���������µ�ְ����ţ�";
			cin >> newId;

			cout << "�������µ�������";
			cin >> newName;

			cout << "��ѡ���ְ���Ĳ��ű�ţ�\n" << endl;
			cout << "1.��ְͨ��\n2.����\n3.�ϰ�" << endl;
			cin >> dSelect;

			Worker* worker = nullptr;
			switch (dSelect)
			{
			case  1:
				worker = new Employee(newId, newName, 1);
				break;
			case  2:
				worker = new Manager(newId, newName, 2);
				break;
			case  3:
				worker = new Boss(newId, newName, 3);
				break;
			default:
				break;
			}
			this->m_EmpArray[index] = worker;
			cout << "�޸ĳɹ���" << endl;
			this->save();
		}
		else
		{
			cout << "�����ڸ�ְ����" << endl;
		}
	}
	system("pause");
	system("cls");
}


void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ�Ϊ�ջ򲻴��ڣ�" << endl;
	}
	else
	{
		cout << "��������ҵķ�ʽ��\n1.����Ų���\n2.����������\n";
		int select;
		cin >> select;

		if (select == 1)
		{
			int id;
			cout << "������Ҫ���ҵ�ְ����ţ�";
			cin >> id;

			int index = IsExist(id);
			if (index != -1)
			{
				cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
				this->m_EmpArray[index]->showInfo();
			}
			else
			{
				cout << "����ʧ�ܣ������ڸ�ְ��" << endl;
			}
		}
		else if (select == 2)
		{
			string name;
			cout << "��������ҵ�������";
			cin >> name;
			bool flag = false;
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "���ҳɹ���ְ�����Ϊ��"
						<< this->m_EmpArray[i]->m_Id
						<< "��ְ����Ϣ���£�" << endl;

					flag = true;
					this->m_EmpArray[i]->showInfo();
				}
			}
			if (flag == false) 
			{
				cout << "����ʧ�ܣ������ڸ�ְ��" << endl;
			}
		}
		else
		{
			cout << "��������" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ�Ϊ�ջ򲻴��ڣ�" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ʽ��" << endl;
		cout << "1.��ְ���Ž�������" << endl;
		cout << "2.��ְ���Ž��н���" << endl;

		int select = 0;
		cin >> select;
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minOrMax = i;
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1)
				{
					if (this->m_EmpArray[j]->m_Id < this->m_EmpArray[minOrMax]->m_Id)
					{
						minOrMax = j;
					}
				}
				else
				{
					if (this->m_EmpArray[j]->m_Id > this->m_EmpArray[minOrMax]->m_Id)
					{
						minOrMax = j;
					}
				}
			}
			if (minOrMax != i)
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = temp;
			}
		}
		cout << "����ɹ���������ְ����Ϣ���£�" << endl;
		this->save();
		this->Show_Emp();
	}
	system("pause");
	system("cls");
}


void WorkerManager::Clean_File()
{
	cout<<"�Ƿ����������Ϣ��(Y/N)"<<endl;
	char ch;
	cin>>ch;
	if (ch == 'Y' || ch == 'y')
	{
		ofstream ofs(FILENAME, ios::out);
		ofs.close();
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}

			delete []this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "��ճɹ���" << endl;
	}
	else if(ch == 'N' || ch == 'n')
	{
		cout<<"ȡ����գ�"<<endl;
	}
	else
	{
		cout<<"��������"<<endl;
	}
	system("pause");
	system("cls");
}



WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (this->m_EmpArray[i] != NULL)
			{
				delete this->m_EmpArray[i];
			}
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = nullptr;
	}
}