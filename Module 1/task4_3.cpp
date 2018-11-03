//
//  main.cpp
//  task4_3
//
//  Created by Artur on 04/10/2018.
//  Copyright © 2018 Artur Sardaryan. All rights reserved.
//

/*
Решение всех задач данного раздела предполагает использование кучи, реализованной в виде класса.

 4_3. Тупики.
 На вокзале есть некоторое количество тупиков, куда прибывают электрички. Этот вокзал является их конечной станцией. Дано расписание движения электричек, в котором для каждой электрички указано время ее прибытия, а также время отправления в следующий рейс. Электрички в расписании упорядочены по времени прибытия. Когда электричка прибывает, ее ставят в свободный тупик с минимальным номером. При этом если электричка из какого-то тупика отправилась в момент времени X, то электричку, которая прибывает в момент времени X, в этот тупик ставить нельзя, а электричку, прибывающую в момент X+1 — можно.
 В данный момент на вокзале достаточное количество тупиков для работы по расписанию.
 Напишите программу, которая по данному расписанию определяет, какое минимальное количество тупиков требуется для работы вокзала.
 Формат входных данных. Вначале вводится n - количество электричек в расписании. Затем вводится n строк для каждой электрички, в строке - время прибытия и время отправления. Время - натуральное число от 0 до 10^9. Строки в расписании упорядочены по времени прибытия.
 Формат выходных данных. Натуральное число - минимальное количеством тупиков.
 Максимальное время: 50мс, память: 5Мб.

 in
 1
 10 20

 out
 1
 
 
 in
 2
 10 20
 20 25

 out
 2
 
 
 in
 3
 10 20
 20 25
 21 30

 out
 2

 
*/

#include <iostream>

#define BUFFER_GROW_COFFICIENT 2
#define INITIAL_BUFFER_SIZE 10

struct Train {
    int arrival;
    int departure;
    Train() { arrival = 0; departure = 0; }
};

const bool operator<(const Train& left, const Train& right) {
    return left.departure < right.departure;
}

const bool operator>=(const Train& left, const Train& right) {
    return left.departure >= right.departure;
}


template <class T>
class Heap {
private:
    T* items;
    int bufferSize;
    int realSize;
    void siftUp(int i);
    void siftDown(int i);
    void grow();
public:
    Heap();
    ~Heap();
    T first();
    void enqueue(const T& item);
    void dequeue();
    int count() { return realSize; }
    bool isEmpty() { return realSize == 0; }
};

template <class T>
Heap<T>::Heap() {
    bufferSize = INITIAL_BUFFER_SIZE;
    items = new T[bufferSize];
    realSize = 0;
}

template <class T>
Heap<T>::~Heap() {
    delete[] items;
}

template <class T>
void Heap<T>::grow() {
    int newBufferSize = bufferSize * BUFFER_GROW_COFFICIENT;
    T* newBuffer = new T[newBufferSize];
    for (int i = 0; i < bufferSize; i++) {
        newBuffer[i] = items[i];
    }
    delete[] items;
    items = newBuffer;
    bufferSize = newBufferSize;
}

template <class T>
T Heap<T>::first() {
    if (isEmpty()) {
        throw "Heap is empty";
    }
    return items[0];
}

template <class T>
void Heap<T>::siftUp(int i) {
    while (i > 0) {
        int daddy = (i - 1)/ 2;
        if (items[i] >= items[daddy]) {
            return;
        }
        std::swap(items[i], items[daddy]);
        i = daddy;
    }
}

template <class T>
void Heap<T>::siftDown(int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    int largest = i;
    if (left < realSize && items[left] < items[i]) {
        largest = left;
    }
    if (right < realSize && items[right] < items[largest]) {
        largest = right;
    }
    if (largest != i) {
        std::swap(items[i], items[largest]);
        siftDown(largest);
    }
}

template <class T>
void Heap<T>::enqueue(const T& item) {
    if (realSize >= bufferSize) {
        grow();
    }
    
    items[realSize++] = item;
    siftUp(realSize - 1);
}

template <class T>
void Heap<T>::dequeue() {
    if (isEmpty()) {
        return;
    }
    
    items[0] = items[--realSize];
    siftDown(0);
}

void addTrain(Heap<Train>* station, Train train) {
    while (!station->isEmpty() && station->first().departure < train.arrival) {
        station->dequeue();
    }
    
    station->enqueue(train);
}

int main(int argc, const char * argv[]) {
    int trainsCount;
    std::cin >> trainsCount;
    Heap<Train>* station = new Heap<Train>;
    int maxCount = 0;
    
    for (int i = 0; i < trainsCount; i++) {
        Train train;
        std::cin >> train.arrival;
        std::cin >> train.departure;
        addTrain(station, train);
        
        if (station->count() > maxCount) {
            maxCount = station->count();
        }
    }
    
    std::cout << maxCount;
    
    delete station;
    return 0;
}
