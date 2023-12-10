#include <iostream>
using namespace std;

void bubble_sort(int a[], int n, int& comp, int& mov) {
    int i, j, t;
    for (i = 0; i < n - 1; ++i) {
        for (j = 0; j < n - i - 1; ++j) {
            comp++;
            if (a[j + 1] < a[j]) {
                t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
                mov += 3;
            }
        }
    }
}

void selection_sort(int a[], int n, int& comp, int& mov) {
    int i, j, iMin, t;
    for (j = 0; j < n - 1; ++j) {
        iMin = j;
        mov++;
        for (i = j + 1; i < n; ++i) {
            comp++;
            if (a[i] < a[iMin]) {
                iMin = i;
                mov++;
            }
        }
        comp++;
        if (iMin != j) {
            t = a[iMin];
            a[iMin] = a[j];
            a[j] = t;
            mov += 3;
        }
    }
}

void insertion_sort(int a[], int n, int& comp, int& mov) {
    int i, j, t;
    for (i = 1; i < n; ++i) {
        t = a[i];
        mov++;
        for (j = i; j > 0 && t < a[j - 1]; --j) {
            a[j] = a[j - 1];
            mov++;
            comp++;
        }
        a[j] = t;
    }
}

void shell_sort(int a[], int n, int& comp, int& mov) {
    int i, j, t, h = 1;
    while (h < n / 3) {
        h = 3 * h + 1;
        comp++;
    }
    while (h >= 1) {
        for (i = h; i < n; ++i) {
            t = a[i];
            mov++;
            for (j = i; j >= h && t < a[j - h]; j -= h) {
                comp++;
                a[j] = a[j - h];
                mov++;
            }
            a[j] = t;
            mov++;
        }
        h /= 3;
    }
}

int main()
{
    int A100[100];
    int A1000[1000];
    int A10000[10000];
    int A100000[100000];
    int T = 10;
    int j = 0;
    int comp = 0;
    int mov = 0;
    while (j < T) {
        for (int i = 0; i < 100; i++) {
            A100[i] = rand();
        }
        for (int i = 0; i < 1000; i++) {
            A1000[i] = rand();
        }
        for (int i = 0; i < 10000; i++) {
            A10000[i] = rand();
        }
        for (int i = 0; i < 100000; i++) {
            A100000[i] = rand();
        }
        bubble_sort(A100, 100, comp, mov);
        cout << comp << " " << mov << endl;
        comp = 0;
        mov = 0;
        bubble_sort(A1000, 1000, comp, mov);
        cout << comp << " " << mov << endl;
        comp = 0;
        mov = 0;
        bubble_sort(A10000, 10000, comp, mov);
        cout << comp << " " << mov << endl;
        comp = 0;
        mov = 0;
        bubble_sort(A100000, 100000, comp, mov);
        cout << comp << " " << mov << endl;
        comp = 0;
        mov = 0;
        j++;
    }
}