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
    void push_back(int item);
    int pop_front();
    int back();
    int front();
    ~Queue();
};

