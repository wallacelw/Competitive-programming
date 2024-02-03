## Strongly Connected Components

A *SCC* is a maximal subgraph in which every vertex is reachable from any vertex inside this same subgraph!

**Property:** An inverted graph has the same SCCs

### Kosaraju Algorithm

Used for **Finding Strongly Connected Somponents** (SCCs) in a *directed graph* (digraph).

**Complexity** O(1) -> O(V + E), linear on number of edges and vertices.

**Remember** to also construct the inverse graph (*gi*).

```cpp
vector<vll> g(MAX, vll());
vector<vll> gi(MAX, vll()); // inverted edges
bool vis[MAX]; // visited vertice?
ll component[MAX]; // connected component of each vertice
stack<ll> st; // for inverting order of transversal

void dfs(ll u) {
    vis[u] = 1;
    for(auto v : g[u]) if (!vis[v]) dfs(v);
    st.push(u);
}

void dfs2(ll u, ll c) {
    component[u] = c;
    for(auto v : gi[u]) if (!component[v]) dfs2(v, c);
}

// 1 - idx
void kosaraju(ll n){
    for(ll i=1; i<=n; i++) if (!vis[i]) dfs(i);

    while(!st.empty()) {
        ll u = st.top(); st.pop();
        if (!component[u]) dfs2(u, u);
    }
}
```

#### Condensation Graph

*AKA:* condensate/convert all SCC's into single vertices and create a new graph, which is a **DAG** (Directed Acyclic Graph)

Kosaraju uses the same order as topological sort, therefore the order that components are discovered is the same!
 
```cpp
vector<vll> gc(MAX, vll()); // Condensation Graph

void condensate(ll n){
    for(ll u=1; u<=n; u++)
        for(auto v : g[u]) if (component[v] != component[u])
            gc[ component[u] ].pb( component[v] );
}
```
