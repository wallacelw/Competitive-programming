## Kosaraju

Used for Finding strongly connected components (SCC)

**Complexity** O(1) -> O(V + E), linear on number of edges and vertices 

```cpp
void dfs(ll u) {
    vis[u] = 1;
    for(auto v : g[u]) if (!vis[v]) dfs(v);
    pilha.push(u);
}

void dfs2(ll u, ll c) {
    vis[u] = 1; component[u] = c;
    for(auto v : gi[u]) if (!vis[v]) dfs2(v, c);
}

// 1 - idx
void kosaraju(ll n){
    memset(vis, 0, sizeof(vis));
    for(ll i=1; i<=n; i++) if (!vis[i]) dfs(i);

    memset(vis, 0, sizeof(vis));
    memset(component, 0, sizeof(component));
    
    while(!pilha.empty()) {
        ll u = pilha.top(); pilha.pop();
        if (!vis[u]) dfs2(u, u);
    }
}
```

### Can be extended to generate a Condensation Graph

AKA: condensate/convert all SCC's into single vertices and create a new graph

```cpp
vector<vll> gc(MAX, vll()); // Condensation Graph

void condensate(ll n){
    for(ll u=1; u<=n; u++)
        for(auto v : g[u]) if (component[v] != component[u])
            gc[ component[u] ].pb( component[v] );
}
```
