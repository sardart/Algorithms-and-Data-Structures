//
//  main.cpp
//  task2_1
//
//  Created by Artur on 04/10/2018.
//  Copyright © 2018 Artur Sardaryan. All rights reserved.
//


/*
 
 2_1. Дан отсортированный массив целых чисел A[0..n-1] и массив целых чисел B[0..m-1]. Для каждого элемента массива B[i] найдите минимальный индекс k минимального элемента массива A, равного или превосходящего B[i]: A[k] >= B[i]. Если такого элемента нет, выведите n. Время работы поиска k для каждого элемента B[i]: O(log(k)).
 n, m ≤ 10000.
 Формат входных данных.
 В первой строчке записаны числа n и m. Во второй и третьей массивы A и B соответственно.
 
 in
 2 1
 1 2
 2
 
 out
 1
 
 
 in
 4 3
 2 4 5 7
 4 6 1
 
 out
 1 3 0
 
 */


#include <iostream>

int findIndex(const int *a, int size, int value);
int binSearch (const int* array, int arraySize, int value);
void calculateResultArray(const int* a, int n, const int* b, int m, int* result);

int main(int argc, const char * argv[]) {
    int n, m;
    std::cin >> n;
    std::cin >> m;
    
    int *a = new int[n];
    int *b = new int[m];
    int *result = new int[m];
    
    for(int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    for(int i = 0; i < m; i++) {
        std::cin >> b[i];
    }
    
    calculateResultArray(a, n, b, m, result);
    for(int i = 0; i < m; i++) {
        std::cout << result[i] << " ";
    }
    
    delete[] a;
    delete[] b;
    delete[] result;
    
    return 0;
}

void calculateResultArray(const int* a, int n, const int* b, int m, int* result) {
    for (int i = 0; i < m; i++) {
        result[i] = findIndex(a, n, b[i]);
    }
}

int findIndex(const int *array, int arraySize, int value) {
    if (value > array[arraySize - 1]) {
        return arraySize;
    } else if (value <= array[0]) {
        return 0;
    }
    
    int k = 1;
    while (value > array[k]) {
        int tmp = k * 2;
        if (tmp < arraySize) {
            k = tmp;
        } else {
            k = arraySize - 1;
        }
    }
    return binSearch(array, k, value);
}

int binSearch (const int* array, int arraySize, int value) {
    int first = arraySize / 2;
    int last = arraySize;
    while (first < last) {
        int middle = (first + last) / 2;
        if (array[middle] < value) {
            first = middle + 1;
        } else {
            last = middle;
        }
    }
    return first;
}
