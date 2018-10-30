//
//  main.cpp
//  task3_3
//
//  Created by Artur on 14/10/2018.
//  Copyright © 2018 Artur Sardaryan. All rights reserved.
//

/*
 Во всех задачах из следующего списка следует написать структуру данных, обрабатывающую команды push* и pop*.
 Формат входных данных.
 В первой строке количество команд n. n ≤ 1000000.
 Каждая команда задаётся как 2 целых числа: a b.
 a = 1 - push front
 a = 2 - pop front
 a = 3 - push back
 a = 4 - pop back
 Команды добавления элемента 1 и 3 заданы с неотрицательным параметром b.
 Для очереди используются команды 2 и 3. Для дека используются все четыре команды.
 Если дана команда pop*, то число b - ожидаемое значение. Если команда pop вызвана для пустой структуры данных, то ожидается “-1”.
 Формат выходных данных.
 Требуется напечатать YES - если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.
 
 3_3. Реализовать очередь с помощью двух стеков. Использовать стек, реализованный с помощью динамического буфера.
 
 in
 3
 3 44
 3 50
 2 44
 
 out
 YES
 
 in
 2
 2 -1
 3 10
 
 out
 YES
 
 
 in
 2
 3 44
 2 66
 
 out
 NO
 
 */

#include <iostream>

#define BUFFER_GROW_COFFICIENT 2
#define INITIAL_BUFFER_SIZE 10


template <class T>
class Stack {
private:
    T* buffer;
    int bufferSize;
    int top;
    void grow();
public:
    Stack();
    ~Stack() { delete[] buffer; }
    void push (const T& a);
    T pop();
    int count() { return top + 1; }
    bool isEmpty() const { return top == -1; }
};

template <class T>
class Queue {
private:
    Stack<T>* pushStack;
    Stack<T>* popStack;
public:
    Queue();
    ~Queue() { delete pushStack; delete popStack; }
    T popFront();
    bool isEmpty() { return pushStack->isEmpty() && popStack->isEmpty(); }
    void pushBack(const T& a);
};


template <class T>
Stack<T>::Stack() {
    bufferSize = INITIAL_BUFFER_SIZE;
    buffer = new T[bufferSize];
    top = -1;
}

template <class T>
void Stack<T>::push(const T& a) {
    if (top + 1 >= bufferSize) {
        grow();
    }
    buffer[++top] = a;
}

template <class T>
T Stack<T>::pop() {
    if (isEmpty()) {
        throw "Empty stack";
    }
    
    return buffer[top--];
}

template <class T>
void Stack<T>::grow() {
    int newBufferSize = bufferSize * BUFFER_GROW_COFFICIENT;
    T *newBuffer = new T[newBufferSize];
    if (!isEmpty()) {
        for (int i = 0; i < top + 1; i++) {
            newBuffer[i] = buffer[i];
        }
    }
    delete[] buffer;
    buffer = newBuffer;
    bufferSize = newBufferSize;
}

template <class T>
Queue<T>::Queue() {
    pushStack = new Stack<T>();
    popStack = new Stack<T>();
}

template <class T>
T Queue<T>::popFront() {
    if (popStack->isEmpty()) {
        while (!pushStack->isEmpty()) {
            popStack->push(pushStack->pop());
        }
    }
    
    return popStack->pop();
}

template <class T>
void Queue<T>::pushBack(const T& a) {
    pushStack->push(a);
}

template <class T>
bool perfomComand(Queue<T>* queue, int comand, T b) {
    switch (comand) {
        case 2:
            if (queue->isEmpty()) {
                if (b == -1) {
                    return true;
                } else {
                    return false;
                }
            }
            
            if (queue->popFront() == b) {
                return true;
            } else {
                return false;
            }
            
        case 3:
            queue->pushBack(b);
            return true;
            
        default:
            return false;
    }
}

int main(int argc, const char * argv[]) {
    
    //data type
    typedef int T;
    
    int comandsCount;
    Queue<T>* queue = new Queue<T>();
    std::cin >> comandsCount;
    
    for (int i = 0; i < comandsCount; i++) {
        int comand;
        T b;
        std::cin >> comand;
        std::cin >> b;
        if (!perfomComand(queue, comand, b)) {
            std::cout << "NO";
            
            delete queue;
            return 0;
        }
    }
    
    std::cout << "YES";
    
    delete queue;
    return 0;
}
