// Questions 3
#include <limits.h>
#include <stdio.h>
#define V 9

// A utility function to find the vertex with minimum disance value, from
// the set of vertices not yet included in shortest path tree
//They hide pretty well
int mindistance(int dis[], bool spathSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (spathSet[v] == false && dis[v] <= min)
            min = dis[v], min_index = v;

    return min_index;
}

// A utility function to print the constructed disance array
void printSolution(int dis[])
{
    printf("Vertex \t\t disance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, dis[i]);
}

void Algo(int graph[V][V], int src)
{
    int dis[V];
    bool spathSet[V];

    // Initialize all disances as INFINITE and stpSet[] as false
    // because why not
    for (int i = 0; i < V; i++)
        dis[i] = INT_MAX, spathSet[i] = false;

    // disance of source vertex from itself is always 0 cause 1 is too much
    dis[src] = 0;

    // Find shortest path for all vertices
    // no reasons to find the longest one
    for (int count = 0; count < V - 1; count++) {
        int u = mindistance(dis, spathSet);

        // Mark the picked vertex as processed
        spathSet[u] = true;

        // Update dis value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < V; v++)
            if (!spathSet[v] && graph[u][v] && dis[u] != INT_MAX
                && dis[u] + graph[u][v] < dis[v])
                dis[v] = dis[u] + graph[u][v];
    }

    // print the constructed disance array
    printSolution(dis);
}

int main()
{
    // Here is an example graph
    int graph[V][V] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
                        { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
                        { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
                        { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
                        { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
                        { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
                        { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
                        { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
                        { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };

    Algo(graph, 0);

    return 0;
}
