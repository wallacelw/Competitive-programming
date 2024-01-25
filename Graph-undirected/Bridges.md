## Bridges ( Cut Edges )

*Bridges and Articulation Points are concepts for **undirected** graphs!*

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
    for(ll i=1; i<=n; i++) if (!tin[i])
        dfs(i);
}
```

### Bridge Tree

Ignoring bridges, and merging **Vertices**, one can obtain a *Bridge Tree*.

Each of these condensated group of **Vertices** is called a *2-edge connected component*, and as the following properties:

    - For each pair of vertices {A, B} inside the same connected component, there are at least 2 distinct paths from A to B (may repeat vertices).

```cpp
// g: u -> {v, edge id}
vector<vector<pll>> g(MAX);
vector<vll> gc(MAX);
ll timer = 1;
ll tin[MAX], low[MAX], comp[MAX];
bool isBridge[MAX];

void dfs(ll u, ll p = -1) {
    tin[u] = low[u] = timer++;
    for(auto [v, id] : g[u]) if (v != p) {
        if (tin[v])
            low[u] = min(low[u], tin[v]); 
        else {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > tin[u])
                isBridge[id] = 1;
        }   
    }
}

void dfs2(ll u, ll c, ll p = -1) {
    comp[u] = c;
    for(auto [v, id] : g[u]) if (v != p) {
        if (isBridge[id]) continue;
        if (!comp[v]) dfs2(v, c, u);
    }
}

void bridgeTree(ll n) {
    // find bridges
    for(ll i=1; i<=n; i++) if (!tin[i])
        dfs(i);

    // find components
    for(ll i=1; i<=n; i++) if (!comp[i]) 
        dfs2(i, i);

    // condensate into a TREE (or TREES if disconnected)
    for(ll u=1; u<=n; u++) {
        for(auto [v, id] : g[u]) {
            if (comp[u] != comp[v]) {
                gc[comp[u]].pb(comp[v]);
            }
        }
    }
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

ll dfs(ll u, ll p = -1) {
    ll children = 0;
    low[u] = tin[u] = timer++;
    for(auto v : g[u]) if (v != p) {
        if (tin[v]) // visited
            low[u] = min(low[u], tin[v]);
        else { // not visited
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

### Block-Cut Tree

Ignoring Articulation Points, and merging **Edges** into a single new **Vertex**, one can obtain a *Block-Cut Tree*.

Each edge in the block-cut tree connects an Articulation Point and a biconnected component.

Each of these condensated group of **Edges** is called a *2-vertex connected component* or *biconnected component*, and as the following properties:

    - For each pair of edges, there is a cycle that contains both edges
    - For each pair of vertices {A, B} inside the same connected component, there are at least 2 distinct paths from A to B (which do not repeat vertices).

**Special-Case:** Every bridge is itself a biconnected component

```cpp
// Block-Cut Tree (bruno monteiro)
//
// Cria a block-cut tree, uma arvore com os blocos
// e os pontos de articulacao
// Blocos sao as componentes 2-vertice-conexos maximais
// Uma 2-coloracao da arvore eh tal que uma cor sao
// os componentes, e a outra cor sao os pontos de articulacao
//
// Funciona para grafo nao conexo
//
// isAP[i] responde o numero de novas componentes conexas
// criadas apos a remocao de i do grafo g
// Se isAP[i] >= 1, i eh ponto de articulacao
// 
// Para todo i < blocks.size()
// blocks[i] eh uma componente 2-vertce-conexa maximal
// blockEdges[i] sao as arestas do bloco i
//
// tree é a arvore block-cut-tree
// tree[i] eh um vertice da arvore que corresponde ao bloco i
// 
// comp[i] responde a qual vertice da arvore vertice i pertence
//
// Arvore tem no maximo 2n vertices
//
// O(n+m)

// 0-idx graph!!!
vector<vll> g(MAX), tree, blocks; // 2-vertex-connected-COMPonentS
vector<vector<pll>> blockEdges;
stack<ll> st; // st for vertices,
stack<pll> st2; // st2 for edges
vector<ll> low, tin, comp, isAP;
ll timer = 1;

void dfs(ll u, ll p = -1) {
    low[u] = tin[u] = timer++;
    
    st.push(u);

    // add only back-edges to stack
    if (p != -1) st2.push({u, p}); 
    for(auto v : g[u]) if (v != p) {
        if (tin[v] != -1) // visited
            st2.push({u, v});
    }

    for(auto v : g[u]) if (v != p) {
        if (tin[v] != -1) // visited
            low[u] = min(low[u], tin[v]);
        else { // not visited
            dfs(v, u);
            low[u] = min(low[u], low[v]);

            if (low[v] >= tin[u]) {
                isAP[u] += 1;
                
                blocks.pb(vll(1, u));
                while(blocks.back().back() != v)
                    blocks.back().pb(st.top()), st.pop();
                
                blockEdges.pb(vector<pll>(1, st2.top())), st2.pop();
                while(blockEdges.back().back() != pair<ll, ll>(v, u))
                    blockEdges.back().pb(st2.top()), st2.pop();
            }
        }
    }

    // corner case: root
    if (p == -1 and isAP[u]) isAP[u]--;
}

void blockCutTree(ll n) {
    
    // initialize vectors and reset
    tree.clear(), blocks.clear(), blockEdges.clear();
    st = stack<ll>(), st2 = stack<pll>();
    tin.assign(n, -1);
    low.assign(n, 0), comp.assign(n, 0), isAP.assign(n, 0);
    timer = 1;

    // find Articulation Points
    for(ll i=0; i<n; i++) if (tin[i] == -1)
        dfs(i);

    // set component id for APs
    tree.assign(blocks.size(), vll());
    for(ll i=0; i<n; i++) if (isAP[i])
        comp[i] = tree.size(), tree.pb(vll()); 
    
    // set component id for non-APs and construct tree
    for(ll u=0; u<(ll)blocks.size(); u++) {
        for(auto v : blocks[u]) {
            if (!isAP[v]) 
                comp[v] = u;
            else 
                tree[u].pb(comp[v]), tree[comp[v]].pb(u);
        }
    }
}
```