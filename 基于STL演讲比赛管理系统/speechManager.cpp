#include"speechManager.h"

SpeechManager::SpeechManager()
{
	this->initSpeech();

	this->createSpeaker();

	this->loadRecord();
}


void SpeechManager::show_Menu()
{
	cout << "*********************************" << endl;
	cout << "*********欢迎参加演讲比赛********" << endl;
	cout << "**********1.开始演讲比赛*********" << endl;
	cout << "**********2.查看往届记录*********" << endl;
	cout << "**********3.清空比赛记录*********" << endl;
	cout << "**********0.退出比赛程序*********" << endl;
	cout << "*********************************" << endl;
	cout << endl;
}




void SpeechManager::exitSystem()
{
	cout << "欢迎下次再来！" << endl;
	exit(0);
}


void SpeechManager::initSpeech()
{
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();

	this->m_Index = 1;
	this->m_Record.clear();
}

void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCEDFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string  name = "选手";
		name += nameSeed[i];

		Speaker sp;
		sp.m_Name = name;

		for (int j = 0; j < 2; j++)
		{
			sp.m_Score[j] = 0;
		}

		this->v1.push_back(i + 10001);

		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}

void SpeechManager::startSpeech()
{
	speechDraw();

	speechContest();

	showScore();

	this->m_Index++;

	speechDraw();

	speechContest();

	showScore();

	saveRecord();

	initSpeech();

	createSpeaker();

	loadRecord();



	cout << "**比赛结束，感谢您的参与！**" << endl;
	system("pause");
	system("cls");



}

void SpeechManager::speechDraw()
{

	cout << "**正在进行第" << this->m_Index << "轮抽签**" << endl;
	cout << "-------------------------------------" << endl;
	cout << "抽签后演讲顺序如下：" << endl;
	if (this->m_Index == 1)
	{
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "-------------------------------------" << endl;
	system("pause");
	cout << endl;

}

void SpeechManager::speechContest()
{
	cout << "**第" << this->m_Index << "轮比赛正式开始**" << endl;

	multimap<double, int, greater<double>> groupScore;
	int num = 0;

	vector<int> v_Src;
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;
		deque<double> d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600.0) / 10.f;
			//cout<<score<<" ";
			d.push_back(score);
		}

		sort(d.begin(), d.end(), greater<double>());
		d.pop_back();
		d.pop_front();

		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double)d.size();
		avg = (int)(avg * 10.0 + 0.5) / 10.0f;

		//cout<<"编号："<<*it<<" 姓名："<<this->m_Speaker[*it].m_Name<<" 平均得分："<<avg<<endl;

		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		groupScore.insert(make_pair(avg, *it));

		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "组得分如下：" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "编号：" << it->second << "  姓名：" << this->m_Speaker[it->second].m_Name << "  成绩："
					<< this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
			}

			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++)
			{
				if (this->m_Index == 1)
				{
					v2.push_back(it->second);
				}
				else
				{
					vVictory.push_back(it->second);
				}
			}

			groupScore.clear();
			cout << endl;
		}
	}

	cout << "**第" << this->m_Index << "轮比赛结束**" << endl;
	system("pause");
	cout << endl;
}


void SpeechManager::showScore()
{
	cout << "**第" << this->m_Index << "轮比赛晋级选手如下**" << endl;

	vector<int> v;
	if (this->m_Index == 1)
	{
		v = v2;
	}
	else
	{
		v = vVictory;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "编号：" << *it << " 姓名：" << this->m_Speaker[*it].m_Name << "  成绩："
			<< this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;
	system("pause");

	this->show_Menu();
}


void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);

	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << ","
			<< this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;

	ofs.close();
	cout << "比赛记录已保存！" << endl;
	this->fileIsEmpty = false;
}

void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);

	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		cout<<"文件不存在！"<<endl;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空！" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	this->fileIsEmpty = false;
	ifs.putback(ch);

	string data;
	int index = 0;
	while (ifs >> data)
	{
		//cout << data << endl;
		vector<string> v;

		int pos = -1;
		int start = 0;
		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				break;
			}
			string temp = data.substr(start, pos - start);
			v.push_back(temp);

			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();

	//for (map<int, vector<string>>::iterator it = this->m_Record.begin(); it != this->m_Record.end(); it++)
	//{
	//	cout << it->first << " " << it->second[0] << " " << it->second[1] << endl;
	//}
}


void SpeechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "文件为空！" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		int num = 1;
		for (map<int, vector<string>>::iterator it = this->m_Record.begin(); it != this->m_Record.end(); it++)
		{
			cout << "第" << num++ << "届 " << endl
				<< "冠军编号：" << it->second[0] << " 得分：" << it->second[1] << endl
				<< "亚军编号：" << it->second[2] << " 得分：" << it->second[3] << endl
				<< "季军编号：" << it->second[4] << " 得分：" << it->second[5] << endl;
			cout << "------------------------------" << endl;
		}
		system("pause");
		system("cls");
	}
}


void SpeechManager::clearRecord()
{
	cout << "是否确定清空?" << endl;
	cout << "1、是" << endl;
	cout << "2、否" << endl;

	int choice;
	cin >> choice;

	if (choice == 1)
	{
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		this->initSpeech();

		this->createSpeaker();

		this->loadRecord();

		cout << "比赛记录已清空！" << endl;
	}
	else
	{
		cout << "取消清空！" << endl;
	}
	system("pause");
	system("cls");
}


SpeechManager::~SpeechManager()
{

}


