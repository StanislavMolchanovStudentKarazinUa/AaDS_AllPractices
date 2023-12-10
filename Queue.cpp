#include "Queue.h"
#include <iostream>
using namespace std;

Queue::Queue(int max_size) {
    arr = new int[max_size];
    this->max_size = max_size;
    int front = 0;
    int back = -1;
    int n = 0;
}

Queue::~Queue() {
    delete[] arr;
}

void Queue::push_back(int a)
{
    if (n == max_size)
    {
        cout << "The queue is full\n";
    }
    else {
        back_index = (back_index + 1) % max_size;
        arr[back_index] = a;
        cout << a << " was inserted" << endl;
        n++;
    }
}

int Queue::pop_front() {
    if (n == 0) {
        cout << "The queue is empty\n";
        return NULL;
    }
    int a = arr[front_index];
    front_index = (front_index + 1) % max_size;
    n--;
    cout << a << " was removed" << endl;
    return a;
}

int Queue::back()
{
    if (n == 0) {
        cout << "The queue is empty\n";
        return NULL;
    }
    return arr[back_index];
}

int Queue::front()
{
    if (n == 0) {
        cout << "The queue is empty\n";
        return NULL;
    }
    return arr[front_index];
}