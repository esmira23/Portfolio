//
//  sort.cpp
//  sort
//
//  Created by Esmira Abdullaieva on 15.02.2021.
//

#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <math.h>

long compares = 0;
long swaps = 0;

using namespace std;

// заповнення масиву рандомними чисоами
void Make_Array(int array[] , int size)
{
    for (int i = 0; i < size; i++)
        array[i] = -10000 + rand() % 20000;

}

// вивід масиву
void Show_Array(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}

// сортування вставками
void Insert_Sort(int array[], int size)
{
    int tmp;
    int j;
    for (int i = 1; i < size; i++) // цикл проходів
    {
        tmp = array[i]; // ініціалізація тимчасової змінної
        j = i-1; // запам'ятовуемо індексу попереднього елемента масиву
        compares++; // кількість порівнянь
        while (j >= 0 && tmp < array[j])
        {
            swaps++; // кількість перестановок
            compares++; // кількість порівнянь
            array[j+1] = array[j]; // перестановка елементів
            j-=1;
        }
        // елементу присвоюємо значення тимчасової змінної
        array[j+1] = tmp;
        

    }
}
    
// сортуванни Шелла-Кнута
void Shell_Sort(int array[], int size)
{
    int h;
    for ( h = 1; h <= (int)log(size)/log(3)-1; h = 3*h + 1) // цикл проходів
    ;
        for (; h>0; h/=3) // зміна кроку
        for (int i = h; i <= size-1; i++)
        {
            int j = i;
            int tmp = array[i]; // ініціалізація тимчасової змінної
//            compares++; // кількість порівнянь
            while (j >= h && tmp < array[j-h])
            {
                compares++; // кількість порівнянь
                swaps++; // кількість перестановок
                array[j]= array[j-h]; // перестановка елементів
                j-=h;
            }
            // елементу присвоюємо значення тимчасової змінної
            array[j] = tmp;
            compares++;
        }
}

int main (){
    int size = 0;
    int arr[100000];
    // задаємо розмір масиву
    cout << "Enter size: " << endl;
    cin >> size;
    
    Make_Array(arr, size);
    // Show_Array(arr, size); // вивід масиву
    cout << endl;
    
    float start_time= clock(); // час початку сортування
    Shell_Sort(arr,size); // сортування вставками
    float end_time = clock(); // час кінця сортування
    
    // Show_Array(arr, size); // вивід масиву
    cout << endl;
    
    cout << "Compares: " << compares << endl; // кількість порівнять
    cout << "Swaps: " << swaps << endl; // кількість перестановок
    float search_time = (end_time - start_time)/1000;
    cout << "Time: " << search_time << endl << endl;
}

