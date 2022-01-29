//
//  list.cpp
//  list
//
//  Created by Esmira Abdullaieva on 30.03.2021.
//

#include <iostream>
#include <string>
#include <cstring>
#include <ctype.h>
#include <cctype>

using namespace std;

struct Node
{
    string key;
    Node *next, *prev;
};

class List
{
private:
    Node *head, *tail;
    int size; // кількість елементів
public:
    List(); // конструктор
    ~List(); // деструктор
    void Show(); // показ списку
    void Add(string key, int pos);
    void AddTail(string key); // додавання елементу в кінець списку
    void AddHead(string key); // додавання елементу в початок списку
    void myfunction(string key);
    void del();
};

List::List()
{
    head = tail = NULL;
    size = 0;
}

List::~List()
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

void List::Show()
{
   if(size == 0)
   {
       cout << "List is empty" << endl;
   }
       else
   {
       Node *tmp = head;
       while(tmp != NULL) // допоки не дійду до кінця
       {
           cout << tmp->key << " ";
           tmp = tmp->next;
       }
   }
    cout << endl;
}

void List::Add(string key, int pos)
{
    if (pos < 1 || pos > size+1)
    {
        cout << "Incorrect position" << endl;
        return;
    }
    if (pos == size + 1)
    {
        AddTail(key);
        return;
    }
    else if (pos == 1)
    {
        // додавання в початок списку
        AddHead(key);
        return;
    }
    
    int i = 1;
    Node *ins = head;
    
    while(i < pos)
    {
        ins = ins->next;
        i++;
    }
    Node *previous = ins->prev;
    
    Node *tmp = new Node;
    tmp->key = key;
    
    previous->next = tmp;
    tmp->next = ins;
    tmp->prev = previous;
    ins->prev = tmp;
    
    size++;
}

void List::AddTail(string key)
{
    Node* tmp = new Node;
    
    tmp->next = NULL;
    tmp->key = key;
    tmp->prev = tail;
    
    if(tail != NULL)
        tail->next = tmp;
    
    if(size == 0)
        head = tail = tmp;
    else
        tail = tmp;
    
    size++;
}

void List::AddHead(string key)
{
    Node* tmp = new Node;
    
    tmp->prev = NULL;
    tmp->key = key;
    tmp->next = head;
    
    if(head != NULL)
        head->prev = tmp;
    
    if(size == 0)
        head = tail = tmp;
    else
        head = tmp;
    
    size++;
}

void List::myfunction(string key)
{
    if (size == 0)
    {
        cout << "List is empty" << endl;
    }
    else
    {
        const char* althabet = {"abcdefghigklmnopqrstuvwxyz"};
        Node* tmp = head;
        string first = tmp->key;
        tmp = tmp->next;
        for(int i = 0; i<size-1; i++)
        {
            if(tmp->key == first){
                tmp = tmp->next;
            }
            else
            {
                string tmps = tmp->key;
                unsigned long pos = 0;
                for(int j = 0; j < tmps.size(); j++)
                {
                    if (j == tmps.size() - 1 and (pos=tmps.find(althabet,0,j)) != -1)
                    {
                        tmps = tmps + ".";
                        cout << tmps.erase(pos,1) << " ";
                    }
                }
                tmp=tmp->next;
            }
        }
        cout << endl;
    }
}

int main()
{
    int answer;
    string input;
    bool enter = true;
    List list;
    cout << "Enter text. To stop - enter word stop:" << endl;
    while(enter == true)
    {
        cin >> input;
        if (input == "stop")
        {
            enter = false;
            break;
        }
        else
        {
            list.AddTail(input);
        }
    }
    while (true)
    {
        cout << "What you want to do with list?" << endl;
        cout << "1. Show list" << endl;
        cout << "2. Add element to head" << endl;
        cout << "3. Add element to tail" << endl;
        cout << "4. Add element to your position" << endl;
        cout << "5. Show new list" << endl;
        cout << "6. Detele list" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter you choose:" << endl;
        cin >> answer;
        cout << endl;
        
    switch (answer) {
        case 1:
            cout << "List:" << endl;
            list.Show();
            cout << endl;
            break;
        case 2:
            cout << "Enter string: " << endl;
            cin >> input;
            cout << endl;
            list.AddHead(input);
            cout << endl;
            break;
        case 3:
            cout << "Enter string: " << endl;
            cin >> input;
            cout << endl;
            list.AddTail(input);
            cout << endl;
            break;
        case 4:
            cout << "Enter string: " << endl;
            cin >> input;
            cout << endl;
            int pos;
            cout << "Enter position: " << endl;
            cin >> pos;
            list.Add(input, pos);
            cout << endl;
            break;
        case 5:
            cout << "New list:" << endl;
            list.myfunction(input);
            cout << endl;
            break;
        case 6:
            list.~List();
            break;
        case 7:
            cout << "Program ended!" << endl;
            return 0;
        default:
            cout << "Wrong input!" << endl;
            break;
    }
    }
    return 0;
}
