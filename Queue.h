#pragma once
#define MAX_QUEUE_SIZE 1000

class Queue {
    int* arr;
    int max_size = 0;
    int front_index = 0;
    int back_index = -1;
    int n = 0;

public:
    Queue(int max_size = MAX_QUEUE_SIZE);
    void push_back(int item);   // додати елемент item в к≥нець черги
    int pop_front();            // вит€гнути елемент з початку черги
    int back();                 // отримати елемент у хвост≥ черги (останн≥й)
    int front();                // отримати елемент у голов≥ черги (перший)
    ~Queue();
};

