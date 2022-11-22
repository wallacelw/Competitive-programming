## Bridges ( Cut Edges )

**Theory:** After constructing a DFS Tree, an edge (u, v) is a bridge if and only if there is no back-edge from *v, or a descendent of v,* to *u, or an ancestor of u*.

To do this efficiently, it's used *tin[i] (entry time of node **i**)* and *low[i] (minimum entry time of all nodes that can be reached from node **i**)*.

```cpp
vector<vll> g(MAX, vll());
bool vis[MAX];
ll tin[MAX], low[MAX];
ll timer;
vpll bridges;

void dfs(ll u, ll p = -1){
    vis[u] = 1;
    tin[u] = low[u] = timer++;
    for(auto v : g[u]) if (v != p) {
        if (vis[v]) low[u] = min(low[u], tin[v]);
        else {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > tin[u])
                bridges.pb( {u, v} );
        }   
    }
}

void find_bridges(ll n) {
    timer = 1;
    memset(vis, 0, sizeof(vis));
    memset(tin, 0, sizeof(tin));
    memset(low, 0, sizeof(low));
    for(ll i=1; i<=n; i++) if (!vis[i]) dfs(i);
}
```

## Articulation Points and Bridges

Finds all Cut-Vertices and Cut-Edges in a single dfs tranversal O(V+E)

**Maybe is working, maybe it's not, needs testing for exquisite graphs, like cliques**

```cpp
vector<vll> g(MAX, vll());
vll tin(MAX, -1), low(MAX, 0);
// tin[] = the first time a node is visited ("time in")
// if tin[u] != -1, u was visited
// low[] = lowest first_time of any node reachable by the current node

ll root = -1, rootChildren = 0, timer = 0;
// root = the root of a dfs transversal, rootChildren = number of direct descedentes of the root

vector<bool> isArticulation(MAX, 0); // this vector exists, because we can define several time if a node is a cut vertice
vll articulations; // cut vertices
vpll bridges; // cut edges

void dfs(ll u, ll p) {
    low[u] = tin[u] = timer++;

    for(auto v : g[u]) if (v != p) {
        if (tin[v] == -1) { // not visited
            if (u == root) rootChildren += 1;

            dfs(v, u);

            if (low[v] >= tin[u]) isArticulation[u] = 1;
            if (low[v] > tin[u]) bridges.pb({u, v});
        }

        low[u] = min(low[u], low[v]);
    }
}

void findBridgesAndPoints(ll n) {
    timer = 0;
    for(ll i=1; i<=n; i++) if (tin[i] == -1) {
        root = i; rootChildren = 0;
        dfs(i, -1);
        if (rootChildren > 1) isArticulation[i] = 1;
    }
    for(ll i=1; i<=n; i++) if (isArticulation[i]) articulations.pb(i);
}
```