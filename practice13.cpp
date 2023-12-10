#include <iostream>
using namespace std;

int partition(int a[], int l, int r, int & comp, int & mov) {
    int pivot, i, j, t;
    pivot = a[l];
    mov++;
    i = l; j = r + 1;

    while (1)
    {
        do { ++i; comp++; } while (a[i] <= pivot && i <= r);
        do {
            --j; comp++;
        } while (a[j] > pivot);
        if (i >= j) {
            comp++; break;
        }
        t = a[i]; a[i] = a[j]; a[j] = t;
        mov += 3;
    }
    t = a[l]; a[l] = a[j]; a[j] = t;
    mov += 3;
    return j;
}


void quickSort(int a[], int l, int r, int& comp, int& mov)
{
    int j;

    if (l < r)
    {
        // divide and conquer
        j = partition(a, l, r, comp, mov);
        mov+=2;
        quickSort(a, l, j - 1, comp, mov);
        quickSort(a, j + 1, r, comp, mov);
        mov += 4;
    }
}

void merge(int a[], int l, int m, int r, int aux[], int& comp, int& mov) {
    int i = l, j = m + 1;
    for (int k = l; k <= r; ++k) { aux[k - l] = a[k]; mov++; comp++; }
    for (int k = l; k <= r; ++k) {
        if (i > m) { a[k] = aux[j++ - l]; comp++; mov++; }
        else if (j > r) {
            a[k] = aux[i++ - l]; comp += 2; mov++;
        }
        else if (aux[i - l] < aux[j - l]) {
            a[k] = aux[i++ - l]; comp += 3; mov++;
        }
        else {
            a[k] = aux[j++ - l]; comp += 3; mov++;
        }
    }
}

void sort_util(int a[], int l, int r, int aux[], int& comp, int& mov) {
    comp++;
    if (l < r) {
        int m = l + (r - l) / 2;
        sort_util(a, l, m, aux, comp, mov);
        sort_util(a, m + 1, r, aux, comp, mov);
        merge(a, l, m, r, aux, comp, mov);
        mov += 7;
    }
}

void merge_sort(int a[], int l, int r, int& comp, int& mov) {
    comp++;
    if (l < r) {
        int* aux = new int[l - r + 1]; // define an auxillary array we will be passing the same array around.
        sort_util(a, l, r, aux, comp, mov);
        mov += 2;
    }
}

int main()
{
    int A100[100];
    int A1000[1000];
    int A10000[10000];
    int A100000[100000];
    int T = 3;
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
        quickSort(A100, 0, 100, comp, mov);
        cout << comp << " " << mov << endl;
        comp = 0;
        mov = 0;
        quickSort(A1000, 0, 1000, comp, mov);
        cout << comp << " " << mov << endl;
        comp = 0;
        mov = 0;
        quickSort(A10000, 0, 10000, comp, mov);
        cout << comp << " " << mov << endl;
        comp = 0;
        mov = 0;
        quickSort(A100000, 0, 100000, comp, mov);
        cout << comp << " " << mov << endl;
        comp = 0;
        mov = 0;
        j++;
    }
}