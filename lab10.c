// Implementation of Kruskal's Algorithm.
#include <stdio.h>
#include <stdlib.h>

// Initialisation of parent[] and rank[] arrays.
void makeSet(int parent[], int rank[], int n)
{
    for(int i = 0; i < n; i += 1)
    {
        parent[i] = i;
        rank[i] = 0;
    }
}

// To find the root of a node.
int findParent(int parent[], int component)
{
    if(parent[component] == component)
        return component;
    return findParent(parent, parent[component]);
}

// Function for union of two sets.
void unionSet(int u, int v, int parent[], int rank[], int n)
{
    // Find the parents of u and v.
    u = findParent(parent, u);
    v = findParent(parent, v);

    // Combining the two trees.
    if(rank[u] < rank[v])
        parent[u] = v;
    else if(rank[u] > rank[v])
        parent[v] = u;
    else
    {
        parent[v] = u;
        rank[u] += 1;
    }
}

// We shall use the standard library function for Quick Sort in C. For that, we define this comparator.
int comparator(const void *p1, const void *p2)
{
    const int (*x)[3] = p1;
    const int (*y)[3] = p2;
    return (*x)[2] - (*y)[2];
}

// Implementing the actual algorithm.
void kruskalAlgo(int n, int edge[n][3])
{
    // Sort the edge array in increasing order of weights.
    qsort(edge, n, sizeof(edge[0]), comparator);
    int parent[n];
    int rank[n];

    // Initialise the sets.
    makeSet(parent, rank, n);
    // To store the total weight of the MST.
    int weight = 0;
    printf("The edges in the finally constructed Minimum Spanning Tree by Kruskal's Algorithm are the following:\n");
    for(int i = 0; i < n; i += 1)
    {
        int v1 = findParent(parent, edge[i][0]);
        int v2 = findParent(parent, edge[i][1]);
        int wt = edge[i][2];
        // If they are disjoint, now we unite them.
        if(v1 != v2)
        {
            unionSet(v1, v2, parent, rank, n);
            weight += wt;
            printf("Edge: %d - %d  Weight = %d\n", edge[i][0], edge[i][1], wt);
        }
    }
    printf("Total weight of the Minimum Spanning Tree comes out to be: %d\n", weight);
}

// Driver function.
int main(void)
{
    int n;
    printf("Enter the total number of edges in the graph: ");
    scanf("%d", &n);
    int edge[n][3];
    for(int i = 0; i < n; i += 1)
    {
        printf("Enter the endpoint vertices (integers) and weight of the next edge (space-separated): ");
        scanf("%d%d%d", &edge[i][0], &edge[i][1], &edge[i][2]);
    }
    kruskalAlgo(n, edge);
    return 0;
}