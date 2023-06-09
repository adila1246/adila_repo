#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100005
#define MAX_M 100005

// Union-Find data structure
int parent[MAX_N];
int rank[MAX_N];

void make_set(int x) {
    parent[x] = x;
    rank[x] = 0;
}

int find_set(int x) {
    if (parent[x] != x) {
        parent[x] = find_set(parent[x]);
    }
    return parent[x];
}

void union_sets(int x, int y) {
    int xset = find_set(x);
    int yset = find_set(y);
    if (rank[xset] < rank[yset]) {
        parent[xset] = yset;
    } else if (rank[xset] > rank[yset]) {
        parent[yset] = xset;
    } else {
        parent[yset] = xset;
        rank[xset]++;
    }
}

// Main function to solve the problem
int makeConnected(int n, int connections[MAX_M][2], int m) {
    if (m < n - 1) {
        return -1;
    }

    // Initialize the Union-Find data structure
    for (int i = 0; i < n; i++) {
        make_set(i);
    }

    // Join the sets
    for (int i = 0; i < m; i++) {
        int x = connections[i][0];
        int y = connections[i][1];
        union_sets(x, y);
    }

    // Count the number of connected components
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (parent[i] == i) {
            count++;
        }
    }

    return count - 1;
}

// Driver code
int main() {
    int n, m;
    int connections[MAX_M][2];

    // Read input
    printf("Enter the number of workstations: ");
    scanf("%d", &n);

    printf("Enter the number of connections: ");
    scanf("%d", &m);

    printf("Enter the connections between workstations: \n");
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &connections[i][0], &connections[i][1]);
    }

    // Solve the problem
    int result = makeConnected(n, connections, m);

    // Print output
    if (result == -1) {
        printf("-1\n");
    } else {
        printf("%d\n", result);
    }

    return 0;
}
