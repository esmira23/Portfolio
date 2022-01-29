//
//  Array_Queue.cpp
//  Array_Queue
//
//  Created by Esmira Abdullaieva on 10.04.2021.
//

#include <iostream>

using namespace std;

class Array_Queue
{
private:
    int size, front, rear;
    int* array;
public:
    Array_Queue(int qsize);
    ~Array_Queue();
    void Show();
    void Enqueue(int item);
    void Dequeue();
};

Array_Queue::Array_Queue(int s)
{
    array = new int[s];
    front = rear = -1;
    size = s;
}

Array_Queue::~Array_Queue()
{
    delete[] array;
}

void Array_Queue::Show()
{
    if(front == -1)
    {
        cout << "Queue is empty" << endl;
    }
    if (rear >= front) // допоки початок не перешов за останній елемент
    {
        for (int i = front; i <= rear; i++)
        cout << array[i] << " ";
    }
    else
    {
        for (int i = front; i < size; i++) // вивід елементів з початку черги до кінця
        cout << array[i] << " ";
        for (int i = 0; i <= rear; i++) // вивід залишку черги
        cout << array[i] << " ";
    }
}

void Array_Queue::Enqueue(int item)
{
    if ((front == 0 && rear == size-1) || ((rear+1)%size == front))
    {
        cout << "Queue is full" << endl;
    }
    else if (front == -1)
        {
            front = rear = 0;
            array [rear] = item;
        }
    else if (rear == size-1 && front != 0)
    {
        rear = 0;
        array [rear] = item;
    }
    else
    {
        rear++;
        array [rear] = item;
    }
}

void Array_Queue::Dequeue()
{
    if(front == -1)
    {
        cout << "Queue is empty" << endl;
    }
    int data = array[front];
    array[front] = -1;
    if (front == rear)
        {
            front = -1;
            rear = -1;
        }
        else if (front == size-1)
            front = 0;
        else
            front++;
    cout << "Deleted element is: " << data << endl;
}

int main()
{
    Array_Queue queue(10);
    queue.Enqueue(1);
    queue.Enqueue(2);
    queue.Enqueue(3);
    queue.Enqueue(4);
    queue.Enqueue(5);
    
    cout << "Array queue:" << endl;
    queue.Show();
    cout << endl;
    
    queue.Dequeue();
    cout << "New array queue:" << endl;
    queue.Show();
    cout << endl;
    return 0;
}

