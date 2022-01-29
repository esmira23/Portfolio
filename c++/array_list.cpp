//
//  array_list.cpp
//  array_list
//
//  Created by Esmira Abdullaieva on 30.03.2021.
//

#include <iostream>
#include <string>

using namespace std;

 class Array
{
private:
    string* item;
    int size;
public:
    Array()
    {
        this->size = 0;
        item = NULL;
    }
    ~Array()
    {
        delete[] this->item;
    }
    void show()
    {
        if (size == 0)
        {
            cout << "Array is empty" << endl;
        }
        else
        {
            for (int i = 0; i < size; i++)
            {
                cout << item[i] << " ";
            }
            cout << endl;
        }
    }
    void add_item(string elem)
    {
        string* tmp = item;
        item = new string[size+1];
        for (int i = 0; i < size; i++)
        {
            item[i] = tmp[i];
        }
        item[size++] = elem;
    }
    void myfunction()
    {
        if (size == 0)
        {
            cout << "Array is empty" << endl;
        }
        else
        {
            int i = 0;
            const char* althabet = { "abcdefghigklmnopqrstuvwxyz" };
            string tmp = item[0];
            for(i = 1;i < size; i++)
            {
                if (item[i] != tmp)
                {
                    string tmps = item[i];
                    unsigned long pos = 0;
                    for(int j = 0; j < tmps.size(); j++)
                    {
                        if (j == tmps.size() - 1 and (pos = tmps.find(althabet, 0, j)) != -1)
                        {
                            tmps = tmps + ".";
                            cout << tmps.erase(pos, 1) << " ";
                        }
                    }
                }
            }
        }
    }
    
    void add()
    {
        int i = 0;
        string* tmp = item;
        tmp = new string[size+1];
        for (i = 0; i < size-1; i++)
        {
            tmp[i] = item[i];
        }
        tmp[size-1] = item[0];
        tmp[size] = item[size-1];
        delete[] item;
        item = tmp;
        size++;
    }
    
//        if (size == 0)
//        {
//            cout << "Array is empty" << endl;
//        }
//        else
//        {
//            int i = 0;
//            string tmp = item[i];
//            for(i = 0;i < size;i++)
//            {
//                if(item[i].size()%2 != 0)
//                {
//                    string tmps = item[i];
//                    cout << tmps.substr(1,tmps.size() - 2) << " ";
//                }
//            }
//            cout << endl;
//        }
//    }
};

int main()
{
    int answer;
    string input;
    bool enter = true;
    Array array;
    cout << "Enter text. If you want to stop - enter world stop:" << endl;
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
            array.add_item(input);
        }
    }
    while (true)
    {
        cout << "What you want to do with list?" << endl;
        cout << "1. Show array" << endl;
        cout << "2. Add element" << endl;
        cout << "3. Show new array" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter you choose:" << endl;
        cin >> answer;
        cout << endl;
        
    switch (answer) {
        case 1:
            cout << "Array:" << endl;
            array.show();
            cout << endl;
            break;
        case 2:
            cout << "Enter element: " << endl;
            cin >> input;
            cout << endl;
            array.add_item(input);
            cout << endl;
            break;
        case 3:
            cout << "New array: " << endl;
            array.add();
            array.show();
            // array.myfunction();
            cout << endl;
            break;
        case 4:
            cout << "Program ended!" << endl;
            return 0;
        default:
            cout << "Wrong input!" << endl;
            break;
    }
    }
    return 0;
}
