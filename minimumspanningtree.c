#include <stdio.h>
#include <stdlib.h>
char getChar(int idx) {
    switch (idx) {
        case 0: return 'L'; // Library
        case 1: return 'H'; // Hostel
        case 2: return 'C'; // Classroom
        case 3: return 'B'; // Lab
        case 4: return 'A'; // Admin
        default: return '?';
    }
}
int comparator(const void* p1, const void* p2) {
    const int (*x)[3] = p1;
    const int (*y)[3] = p2;
    return (*x)[2] - (*y)[2];
}

void makeSet(int parent[], int rank[], int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int findParent(int parent[], int component) {
    if (parent[component] == component)
        return component;
    return parent[component] = findParent(parent, parent[component]);
}

void unionSet(int u, int v, int parent[], int rank[]) {
    u = findParent(parent, u);
    v = findParent(parent, v);
    if (rank[u] < rank[v]) {
        parent[u] = v;
    } else if (rank[u] > rank[v]) {
        parent[v] = u;
    } else {
        parent[v] = u;
        rank[u]++;
    }
}

void kruskalAlgorithm(int vertices, int edgesCount, int edges[edgesCount][3]) {
    qsort(edges, edgesCount, sizeof(edges[0]), comparator);

    int parent[vertices], rank[vertices];
    makeSet(parent, rank, vertices);

    int minCost = 0;

    printf("Selected Edges in the MST:\n");

    for (int i = 0; i < edgesCount; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int wt = edges[i][2];

        int parentU = findParent(parent, u);
        int parentV = findParent(parent, v);

        if (parentU != parentV) {
            printf("%c--%c == %d\n", getChar(u), getChar(v), wt);
            minCost += wt;
            unionSet(parentU, parentV, parent, rank);
        }
    }

    printf("\nTotal Minimum Cost = %d\n", minCost);
}

int main() {
    int edges[8][3] = {
        {0, 1, 4},
        {0, 2, 3},
        {0, 3, 5}, 
        {1, 2, 6}, 
        {1, 4, 5},
        {2, 3, 4}, 
        {2, 4, 7}, 
        {3, 4, 2}  
    };

    kruskalAlgorithm(5, 8, edges);
    return 0;
}