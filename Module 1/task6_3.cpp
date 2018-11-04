//
//  main.cpp
//  task6_3
//
//  Created by Artur on 25/10/2018.
//  Copyright © 2018 Artur Sardaryan. All rights reserved.
//

/*
Даны неотрицательные целые числа n,k и массив целых чисел из [0..10^9] размера n. Требуется найти k-ю порядковую статистику. т.е. напечатать число, которое бы стояло на позиции с индексом k (0..n-1) в отсортированном массиве. Напишите нерекурсивный алгоритм.
Требования к дополнительной памяти: O(n). Требуемое среднее время работы: O(n).
Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении. Описание для случая прохода от начала массива к концу:
Выбирается опорный элемент. Опорный элемент меняется с последним элементом массива.
Во время работы Partition в начале массива содержатся элементы, не бОльшие опорного. Затем располагаются элементы, строго бОльшие опорного. В конце массива лежат нерассмотренные элементы. Последним элементом лежит опорный.
Итератор (индекс) i указывает на начало группы элементов, строго бОльших опорного.
Итератор j больше i, итератор j указывает на первый нерассмотренный элемент.
Шаг алгоритма. Рассматривается элемент, на который указывает j. Если он больше опорного, то сдвигаем j.
Если он не больше опорного, то меняем a[i] и a[j] местами, сдвигаем i и сдвигаем j.
В конце работы алгоритма меняем опорный и элемент, на который указывает итератор i.


6_3. Реализуйте стратегию выбора опорного элемента “случайный элемент”. Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.

in
10 4
1 2 3 4 5 6 7 8 9 10

out
5

in
10 0
3 6 5 7 2 9 8 10 4 1

out
1

in
10 9
0 0 0 0 0 0 0 0 0 1

out
1

*/


#include <iostream>
#include <ctime>
#include <cstdlib>


int randomPosition(int left, int right) {
    srand((unsigned)time(0));
    int position = left + rand() % (right - left);
    return position;
}

template <class T>
int partition(T *array, int left, int right) {
    int pivotPosition = randomPosition(left, right);
    T pivot = array[pivotPosition];
    
    int last = right - 1;
    if (pivotPosition != last) {
        std::swap(array[last], array[pivotPosition]);
    }
    
    int i = left;
    int j = left;
    
    while (j < last) {
        if (pivot > array[j]) {
            std::swap(array[i++], array[j]);
        }
        j++;
    }
    
    if (i != last) {
        std::swap(array[i], array[last]);
    }
    
    return i;
}

template <class T>
const T& searchK(T* array, int arraySize, int k) {
    int left = 0;
    int right = arraySize;
    int pivotPosition = 0;
    
    while (left < right) {
        pivotPosition = partition(array, left, right);
        
        if (pivotPosition == k) {
            return array[pivotPosition];
        } else if (pivotPosition < k) {
            left = pivotPosition + 1;
        } else {
            right = pivotPosition;
        }
    }
    
    return array[pivotPosition];
}


int main(int argc, const char * argv[]) {
    int arraySize;
    int k;
    
    std::cin >> arraySize;
    std::cin >> k;
    
    int* array = new int[arraySize];
    
    for (int i = 0; i < arraySize; i++) {
        std::cin >> array[i];
    }
    
    std::cout << searchK(array, arraySize, k);
    
    delete[] array;
    return 0;
}
