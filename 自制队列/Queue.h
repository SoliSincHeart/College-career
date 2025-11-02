#pragma once
#include <iostream>
using namespace std;
#define Item int
class Queue
{
private:
	struct Node
	{
		Item item;
		Node* next;
	};
	Node* front;
	Node* rear;
	int items;
	const int qsize;
	enum { Q_SIZE = 10 };
public:
	Queue(int qs = Q_SIZE);
	~Queue();
	bool isEmpty() const;
	bool isFull() const;
	int queuecount() const;
	bool enqueue(const Item& item);
	bool dequeue(Item& item);
};



