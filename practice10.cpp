#include <iostream>
using namespace std;
#define N 6

void DijkstraAlgorythm(int graph[N][N], int j) {
    int dist[N];                       
    bool V[N];
    for (int i = 0; i < N; i++) {
        dist[i] = INT_MAX;
        V[i] = false;
    }
    dist[j] = 0;   
    for (int i = 0; i < N; i++)
    {
        int min = INT_MAX, m;
        for (int i = 0; i < 6; i++)
        {
            if (V[i] == false && dist[i] <= min)
            {
                min = dist[i];
                m = i;
            }
        }
        V[m] = true;
        for (int i = 0; i < N; i++)
        {
            if (!V[i] && graph[m][i] && dist[m] != INT_MAX 
                && dist[m] + graph[m][i] < dist[i])
                dist[i] = dist[m] + graph[m][i];
        }
    }
    cout << "Vertex\t\tDistance from source vertex" << endl;
    for (int k = 0; k < N; k++)
    {
        char str = 65 + k;
        cout << str << "\t\t\t" << dist[k] << endl;
    }
}

int main()
{
    int graph[N][N] = {
        {0, 1, 0, 0, 0, 0},
        {3, 0, 1, 0, 0, 0},
        {1, 2, 0, 0, 1, 0},
        {0, 0, 2, 0, 0, 2},
        {0, 0, 4, 1, 0, 0},
        {0, 1, 0, 5, 3, 0}};
    cout << "Input source vertex index: ";
    int j = 0;
    cin >> j;
    DijkstraAlgorythm(graph, j);
    return 0;
}