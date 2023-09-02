## Floyd Warshall

The Floyd–Warshall algorithm provides an alternative way to approach the problem of finding shortest paths. Unlike the other algorithms of this chapter, it finds all shortest paths between the nodes in a single run.

```cpp

for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
           if (i == j) distance[i][j] = 0;
           else if (adj[i][j]) distance[i][j] = adj[i][j];
           else distance[i][j] = INF;
} }

for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
           for (int j = 1; j <= n; j++) {
               distance[i][j] = min(distance[i][j],distance[i][k]+distance[k][j]);
   } }
}

```