#pragma once
#include"speaker.h"
#include<iostream>
#include<map>
#include<algorithm>
#include<deque>
#include<vector>
#include<functional>
#include<numeric>
#include<fstream>
using namespace std;

class SpeechManager
{
public:
	SpeechManager();

	void show_Menu();

	void exitSystem();


	~SpeechManager();

	void initSpeech();

	void createSpeaker();

	void startSpeech();

	void speechDraw();

	void speechContest();

	void showScore();

	void saveRecord();

	void loadRecord();

	void showRecord();

	void clearRecord();

	bool fileIsEmpty;

	map<int,vector<string>> m_Record;

	vector<int> v1;

	vector<int> v2;

	vector<int> vVictory;

	map<int, Speaker> m_Speaker;

	int m_Index;

};
