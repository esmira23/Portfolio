//
//  postfix_calculator.cpp
//  postfix_calculator
//
//  Created by Esmira Abdullaieva on 10.04.2021.
//

#include <iostream>

using namespace std;
struct Node
{
    double data;
    Node* next;
    Node (int elem)
    {
        data = elem;
        next = NULL;
    }
};

class Stack
{
private:
    Node* top;
    int size;
public:
    Stack();
    ~Stack();
    void Show();
    int Top(); //повернення значення вершини
    void Pop(); // видалення
    void Push(int elem); // додавання елемента
    void Info();
    void Capacity(int cap);
};

Stack::Stack()
{
    top = NULL;
    size = 0;
}

Stack::~Stack()
{
    Node *tmp;
    while(top)
    {
        tmp = top->next;
        delete top;
        top = tmp;
        size--;
    }
}

void Stack::Show()
{
    if(size == 0)
    {
        cout << "Stack is empty" << endl;
    }
    else
    {
        Node *tmp = top;
        while(tmp != NULL)
        {
            cout << tmp->data << " ";
            tmp = tmp->next;
        }
        cout << endl;
    }
}

void Stack::Push(int elem) // додавання елементу
{
    Node* tmp = new Node(elem);
    if(size == 0)
    {
        top = tmp;
    }
    else
    {
        tmp->next = top;
        top = tmp;
    }
    size++;
}

void Stack::Pop() // видалення елементу
{
    if(size == 0)
    {
        cout << "Stack is empty" << endl;
    }
    else
    {
        Node* tmp = top;
        tmp = tmp->next;
        delete top;
        top = tmp;
        size--;
    }
}

int Stack::Top() // повернення значення остнанього елемента
{
    if(size == 0)
        cout << "Stack is empty" << endl;
       // cout << "Top element is " <<  (top->data) << endl;
    return (top->data);
}


int main()
{
    Stack calc;
    string postfix = "15 20 - 30 - 40 / 50 60 * -";
    cout << "---- This is a postfix calculator ---- \n" << endl;
    
    for (int i = 0; i < postfix.length(); i++)
    {
        
        if(postfix[i] == ' ' || postfix[i] == ',')
            continue;
        
        else if (isdigit(postfix[i]))
        {
            int n = 0;
            while (i < postfix.length() && isdigit(postfix[i]))
            {
                n *= 10;
                n += postfix[i] - '0';
                i++;
            }
            calc.Push(n);
        }
        
        else
        {
            int n2 = calc.Top();
            calc.Pop();
            int n1 = calc.Top();
            calc.Pop();
            switch (postfix[i])
            {
                case '+':
                    calc.Push(n1+n2);
                    break;
                case '-':
                    calc.Push(n1-n2);
                    break;
                case '*':
                    calc.Push(n1*n2);
                    break;
                case '/':
                    calc.Push(n1/n2);
                    break;
            }
        }
    }
    cout << "Resault is: " << endl;
    calc.Show();
    return 0;
}
