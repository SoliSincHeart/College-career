#include "Queue.h"

Queue::Queue(int qs) :qsize(qs)
{
	front = rear = NULL;
	items = 0;
}

bool Queue::enqueue(const Item& item)
{
	if (isFull())
		return false;
	Node* add = new Node;
	add->item = item;
	add->next = NULL;
	items++;
	if (front == NULL)
		front = add;
	else
		rear->next = add;
	rear = add;
	return true;
}

bool Queue::dequeue(Item& item)
{
	if (front == NULL)
		return false;
	item = front->item;
	items--;
	Node* temp = front;
	front = front->next;
	delete temp;
	if (items == 0)
		rear = NULL;
	return true;
}

bool Queue::isEmpty() const
{
	return items == 0;
}

bool Queue::isFull() const
{
	return items == qsize;
}
int Queue::queuecount() const
{
	return items;
}

Queue::~Queue()
{
	Node* temp = front;
	while (temp != NULL)
	{
		front = front->next;
		delete temp;
		temp = front;
	}
}