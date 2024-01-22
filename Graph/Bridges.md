## Bridges ( Cut Edges )

Also called *isthmus* or *cut arc*.

**Property:** A back-edge is never a bridge!

**Definition** A *lowlink* for a vertice U is the closest vertice to the root reachable using only span edges and a single back-edge, starting in the subtree of U.

**Theory:** After constructing a DFS Tree, an edge (u, v) is a bridge *if and only if* there is no back-edge from *v, or a descendent of v,* to *u, or an ancestor of u*.

To do this efficiently, it's used *tin[i] (entry time of node **i**)* and *low[i] (minimum entry time considering all nodes that can be reached from node **i**)*.

In another words, a edge (u, v) is a back-edge *if and only if* the low[v] > tin[u].

```cpp
vector<vll> g(MAX);
ll timer = 1;
ll tin[MAX], low[MAX];
vector<pll> bridges;

void dfs(ll u, ll p = -1){
    tin[u] = low[u] = timer++;
    for(auto v : g[u]) if (v != p) {
        if (tin[v]) // v was visited ({u,v} is a back-edge)
            // considering a single back-edge:
            low[u] = min(low[u], tin[v]); 
        else { // v wasn't visited ({u, v} is a span-edge)
            dfs(v, u);
            // after low[v] was computed by dfs(v, u):
            low[u] = min(low[u], low[v]);
            if (low[v] > tin[u])
                bridges.pb({u, v});
        }   
    }
}

void findBridges(ll n) {
    timer = 1;
    for(ll i=1; i<=n; i++) if (!tin[i])
        dfs(i);
}
```

## Articulation Points

A vertex U is an articulation points if:

1. a child vertex V has low[v] >= tin[u]
2. the root vertex used has 2 or more children.

```cpp
vector<vll> g(MAX);
ll timer = 1;
ll low[MAX], tin[MAX], isAP[MAX];
// (tin[i] == 0) => not visited

ll dfs(ll u, ll p=-1) {
    ll children = 0;
    low[u] = tin[u] = timer++;
    for(auto v : g[u]) if (v != p) {
        if (tin[v]) low[u] = min(low[u], tin[v]); // visited
        else {
            children++;
            dfs(v, u);
            if (low[v] >= tin[u]) isAP[u] = 1;
            low[u] = min(low[u], low[v]);
        }
    }
    return children;
}

void findAP(ll n) {
    for(ll i=1; i<=n; i++) if (!tin[i])
        isAP[i] = dfs(i) > 1; // root has more than 1 children
}
```