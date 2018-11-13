//
//  main.cpp
//  task5_1
//
//  Created by Artur on 04/10/2018.
//  Copyright © 2018 Artur Sardaryan. All rights reserved.
//

/*
 Во всех задачах данного раздела необходимо реализовать и использовать сортировку слиянием. Общее время работы алгоритма O(n log n).
 
 5_1. Реклама.
 В супермаркете решили оптимизировать показ рекламы. Известно расписание прихода и ухода покупателей (два целых числа). Каждому покупателю необходимо показать минимум 2 рекламы.  Рекламу можно транслировать только в целочисленные моменты времени. Покупатель может видеть рекламу от момента прихода до момента ухода из магазина.
 В каждый момент времени может показываться только одна реклама. Считается, что реклама показывается мгновенно. Если реклама показывается в момент ухода или прихода, то считается, что посетитель успел её посмотреть. Требуется определить минимальное число показов рекламы.
 
 in
 5
 1 10
 10 12
 1 10
 1 10
 23 24
 
 out
 5
 
 */

#include <iostream>
#include <cstring>


struct Guest {
    int in;
    int out;
    Guest() { in = 0; out = 0; }
};

const bool operator<=(const Guest& left, const Guest& right) {
    return left.out <= right.out;
}


template <class T>
void merge(T* firstArray, int firstArraySize, T* secondArray, int secondArraySize, T* tmp) {
    int firstIndex = 0;
    int secondIndex = 0;
    int i = 0;
    
    while (firstIndex < firstArraySize && secondIndex < secondArraySize) {
        if (firstArray[firstIndex] <= secondArray[secondIndex]) {
            tmp[i++] = firstArray[firstIndex++];
        } else {
            tmp[i++] = secondArray[secondIndex++];
        }
    }
    
    while (firstIndex < firstArraySize) {
        tmp[i++] = firstArray[firstIndex++];
    }
    while (secondIndex < secondArraySize) {
        tmp[i++] = secondArray[secondIndex++];
    }
}

template <class T>
void mergeSort(T* array, int arraySize) {
    if (arraySize <= 1) {
        return;
    }
    
    int firstArraySize = arraySize / 2;
    int secondArraySize = arraySize - firstArraySize;
    
    mergeSort(array, firstArraySize);
    mergeSort(array + firstArraySize, secondArraySize);
    
    T* tmp = new T[arraySize];
    
    merge(array, firstArraySize, array + firstArraySize, secondArraySize, tmp);
    memcpy(array, tmp, sizeof(T) * arraySize);
    
    delete[] tmp;
}


int calculateAdvCount(const Guest* guests, int guestsCount) {
    int advCount = 0;
    int firstAdv = -1;
    int secondAdv = -1;
    
    for (int i = 0; i < guestsCount; i++) {
        Guest guest = guests[i];
        
        if (guest.in > secondAdv) {
            firstAdv = guest.out - 1;
            secondAdv = guest.out;
            advCount = advCount + 2;
        } else if (guest.in == secondAdv) {
            firstAdv = secondAdv;
            secondAdv = guest.out;
            advCount++;
        } else if (guest.in > firstAdv && guest.out > secondAdv) {
            firstAdv = secondAdv;
            secondAdv = guest.out;
            advCount++;
        } else if (guest.in > firstAdv && guest.in < secondAdv) {
            firstAdv = guest.out;
            advCount++;
        }
    }
    
    return advCount;
}


int main(int argc, const char * argv[]) {
    int guestsCount;
    std::cin >> guestsCount;

    Guest* guests = new Guest[guestsCount];

    for (int i = 0; i < guestsCount; i++) {
        Guest guest;
        std::cin >> guest.in;
        std::cin >> guest.out;
        guests[i] = guest;
    }

    mergeSort(guests, guestsCount);

    std::cout << calculateAdvCount(guests, guestsCount);
    
    delete[] guests;
    return 0;
}

