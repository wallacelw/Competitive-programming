## Topological Sort

Sort a directed graph with no cycles in an order which each source of an edge is visited before the sink of this edge.

Cannot have cycles, because it would create a contradition of which vertices whould come before.

It can be done with a DFS, appending in the reverse order of transversal.

```cpp
vector<vll> g(MAX, vll());
vector<bool> visited;
vll topological;

void dfs(ll u) {
    visited[u] = 1;
    for(auto v : g[u]) if (!visited[v]) dfs(v);
    topological.pb(u);
}

// 1 - indexed
void topological_sort(ll n) {
    visited.assign(n+1, 0);
    topological.clear();
    for(ll i=1; i<=n; i++) if (!visited[i]) dfs(i);
    reverse(topological.begin(), topological.end());
}
```

