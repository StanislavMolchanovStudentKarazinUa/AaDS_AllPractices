#include "Queue.h"
#include <iostream>
using namespace std;

int main()
{
    cout << "Enter amount: ";
    int n = 0;
    cin >> n;
    if (n <= 0) cout << "Warning: n is 0 or smaller. The queue is defined as empty";
    int m = 0;
    while (m <= 0) {
        cout << "Enter max amount: ";
        cin >> m;
        if (m > 0) break;
        cout << "Max amount is not valid!" << endl;
    }
    Queue q(m);
    int a = 0;
    for (int i = 1; i <= n; i++) {
        cout << "Enter element number " << i << ": ";
        cin >> a;
        q.push_back(a);
    }
    int c = 0;
    int w = 0;
    while (true) {
        cout << "Enter command (1-push, 2-pop, 3-show back, 4-show front, else-exit): ";
        cin >> c;
        if (c == 1) {
            cout << "Enter element: ";
            cin >> a;
            q.push_back(a);
        }
        else if (c == 2) w = q.pop_front();
        else if (c == 3) cout << q.back() << endl;
        else if (c == 4) cout << q.front() << endl;
        else break;
    }
}