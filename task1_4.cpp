//
//  main.cpp
//  task1_4
//
//  Created by Artur on 05/10/2018.
//  Copyright © 2018 Artur Sardaryan. All rights reserved.
//

/*
 4 10
 В каждой задаче, где начальными данными является массив вначале вводится количество элементов, а затем и сами элементы массива.
 
 1_4. “Считалочка”. В круг выстроено N человек, пронумерованных числами от 1 до N. Будем исключать каждого k-ого до тех пор, пока не уцелеет только один человек. (Например, если N=10, k=3, то сначала умрет 3-й, потом 6-й, затем 9-й, затем 2-й, затем 7-й, потом 1-й, потом 8-й, за ним - 5-й, и потом 10-й. Таким образом, уцелеет 4-й.) Необходимо определить номер уцелевшего.
 N, k ≤ 10000.
 
 in
 10 3
 
 out
 4
 
 */

///

#include <iostream>

struct Player {
    int number;
    Player *next;
    Player *prev;
    Player() {
        number = 0;
        next = nullptr;
        prev = nullptr;
    }
};

class Circle {
    Player *tail;
    void remove(Player *player);
public:
    Circle();
    ~Circle();
    void addPlayers(int count);
    void startParty(int k);
    int getSurvivor();
};

Circle::Circle() {
    tail = new Player;
    tail->prev = tail;
    tail->next = tail;
}

Circle::~Circle() {
    Player *tmp = tail;
    while (tmp->next != tail) {
        delete tmp;
        tmp = tmp->next;
    }
}

void Circle::addPlayers(int count) {
    for (int i = 1; i < count + 1; i++) {
        Player *newPlayer = new Player;
        newPlayer->number = i;
        newPlayer->next = tail;
        tail->prev->next = newPlayer;
        newPlayer->prev = tail->prev;
        tail->prev = newPlayer;
    }
}

void Circle::startParty(int k) {
    Player *current;
    int i = 1;
    current = tail->next;
    while (tail->next->next != tail) {
        if (i++ % k == 0) {
            remove(current);
        }
        if (current->next != tail) {
            current = current->next;
        } else {
            current = tail->next;
        }
    }
}

int Circle::getSurvivor() {
    return tail->next->number;
}

void Circle::remove(Player *player) {
    player->prev->next = player->next;
    player->next->prev = player->prev;
    delete player;
}

int main(int argc, const char * argv[]) {
    
    int N, k;
    std::cin >> N;
    std::cin >> k;
    
    if (k == 0 || N == 0)  {
        return 0;
    }
    
    Circle circle;
    circle.addPlayers(N);
    circle.startParty(k);
    
    std::cout << circle.getSurvivor();
    
    return 0;
}

