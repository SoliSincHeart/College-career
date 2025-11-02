#include "Queue.h"
#include <iostream>

int main()
{
    Queue q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(4);
    q.enqueue(5);
    int item;
    for (int i = 0; i < q.queuecount(); i++)
    {
        std::cout <<  q.dequeue(item) << " ";
    }
    std::cout << std::endl;
    return 0;
}