//
//  queue.cpp
//  queue
//
//  Created by Esmira Abdullaieva on 03.04.2021.
//

#include <iostream>

using namespace std;
struct Node
{
    int data;
    Node* next;
    Node (int elem)
    {
        data = elem;
        next = NULL;
    }
};

class Queue
{
private:
    Node *head, *tail;
    int size;
public:
    Queue();
    ~Queue();
    void Show();
    void Enqueue(int item);
    void Dequeue();
    void Info();
};

Queue::Queue()
{
    head = tail = NULL;
    size = 0;
}

Queue::~Queue()
{
    Node *tmp;
    while(head)
    {
        tmp = head->next;
        delete head;
        head = tmp;
        size--;
    }
}

void Queue::Show()
{
   if(size == 0)
   {
       cout << "Queue is empty" << endl;
   }
       else
   {
       Node *tmp = head;
       while(tmp != NULL) // допоки не дійду до кінця
       {
           cout << tmp->data << " ";
           tmp = tmp->next;
       }
   }
    cout << endl;
}

void Queue::Enqueue (int item)
{
    Node* tmp = new Node (item);
    
    if(size == 0)
        head = tail = tmp;
    else
    {
        tail->next = tmp;
        tail = tmp;
    }
    size++;
}

void Queue::Dequeue()
{
    if(size == 0)
    {
        cout << "Queue is empty" << endl;
    }
    else
    {
        Node *tmp = head;
        head = tmp->next;
        if(head == NULL)
        {
            tail = NULL;
        }
        delete tmp;
        size--;
    }
}

void Queue::Info()
{
    cout << "Size: " << this->size << endl;
    cout << "First element: " << (this->head)->data << endl;
    cout << "Last element: " << (this->tail)->data << endl;
}

int main()
{
    Queue queue;
    queue.Enqueue(1);
    queue.Enqueue(2);
    queue.Enqueue(3);
    queue.Enqueue(4);
    queue.Enqueue(5);
    cout << "Queue: ";
    queue.Show();
    queue.Dequeue();
    cout << "Element was deleted" << endl;
    cout << "New queue:" << endl;
    queue.Show();
    cout << "Info:" << endl;
    queue.Info();
    return 0;
}
