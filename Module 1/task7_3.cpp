//
//  main.cpp
//  task7_3
//
//  Created by Artur on 04/10/2018.
//  Copyright © 2018 Artur Sardaryan. All rights reserved.
//

/*
7_3. Binary MSD для long long.
Дан массив неотрицательных целых 64-разрядных чисел. Количество чисел не больше 106. Отсортировать массив методом MSD по битам (бинарный QuickSort).

in
3
4 1000000 7

out
4 7 1000000
 
*/

#include <iostream>


template <typename T>
bool digit(T value, int position) {
    return value & (T)1 << position;
}

template <typename T>
void binQuickSort(T* array, int left, int right, int d) {
    if (d < 0 || left >= right) {
        return;
    }
    
    int i, j;
    for (i = left, j = right; j != i;) {
        while (!digit(array[i], d) && (i < j)) {
            ++i;
        }
        while (digit(array[j], d) && (i < j)) {
            --j;
        }
        
        std::swap(array[i], array[j]);
    }
    
    if (!digit(array[right], d)) {
        ++j;
    }
    
    binQuickSort(array, left, j - 1, d - 1);
    binQuickSort(array, j, right, d - 1);
}


int main(int argc, const char * argv[]) {
    std::cout << "\n";
    typedef long long T;
    
    int arraySize;
    std::cin >> arraySize;
    
    T* array = new T[arraySize];
    
    for (int i = 0; i < arraySize; i++) {
        std::cin >> array[i];
    }
    
    int d = sizeof(T) * 8 - 1;
    binQuickSort(array, 0, arraySize - 1, d);
    
    for (int i = 0; i < arraySize; i++) {
        std::cout << array[i] << " ";
    }
    
    delete[] array;
    return 0;
}
