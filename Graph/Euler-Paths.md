## Euler Path

#### Definitions:

An **Eulerian Path** or **Eulerian Trail** (*Caminho Euleriano*) consists of a path that transverses all **Edges**. 

A special case is the closed path, which is an **Eulerian Circuit** or **Eulerian Cycle** (*Circuito/Ciclo Euleriano*). A graph is considered *eulerian* (**Eulerian Graph**) if it has an Eulerian Circuit.

Similarly, a **Hamiltonian Path** consists of a path that transverses all **Vertices**.

#### Conditions for Eulerian Path existence

To check if it is possible, there is a need for connectivity: 

**connectivity**, all vertices (that contains at least 1 edge) are connected. But there is no need for it to be strongly connected. To check connectivity, you can consider a directed graph as undirected and do a dfs.

and also:

![image](..\..\Aux-Images\EulerianPathExistence.png)

### Hierholzer Algorithm

Find a **Eulerian Path/Circuit** with a linear complexity of *O(Edges)*.

Using an *ordered set* on **Undirected Graphs** increases complexity by *log2(Edges)*. This can be optimized using a *list* with references to each bidirectional edge so that any reversed edge can be erased in *O(1)*.

#### Example 1:

Generating an **Eulerian Path** with Hierholzer in a *Directed Graph*, starting on node *1* and ending on node *n*.

https://cses.fi/problemset/task/1693

```cpp
vector<vll> g(MAX, vll());
vector<vll> ug(MAX, vll()); // undirected graph

vll inDegree(MAX, 0);
vll outDegree(MAX, 0);

vector<bool> vis(MAX, 0);

ll dfsConnected(ll u) {
    ll total = 1; vis[u] = 1;
    for(auto v : ug[u]) if (!vis[v]) {
        total += dfsConnected(v);
    }
    return total;
}

// O(n) -> O(Vertices)
bool checkPossiblePath(ll start, ll end, ll n, ll nodes) {

    // check connectivity
    vis.assign(n+1, 0);
    ll connectedNodes = dfsConnected(1);
    if (connectedNodes != nodes) return 0;

    // check degrees
    for(ll i=1; i<=n; i++) {
        if (i == start) { // start node needs to have 1 more outDegree than inDegree
            if (inDegree[i]+1 != outDegree[i]) return 0;
        }
        else if (i == end) { // end node needs to have 1 more inDegree than outDegree
            if (inDegree[i] != outDegree[i]+1) return 0;
        }
        else {
            if (inDegree[i] != outDegree[i]) return 0;
        }
    }

    return 1;
}

// O(m) -> O(Edges)
// Hierholzer function can be used directly if there is already a garanted existance of an eulerian path/circuit.
vll hierholzer(ll start, ll n) { // generate an eulerian path, assuming there is only 1 end node
    vll ans, pilha, idx(n+1, 0);

    pilha.pb(start);
    while(!pilha.empty()) {
        ll u = pilha.back();
        if (idx[u] < (ll) g[u].size()) {
            pilha.pb( g[u][idx[u]] );
            idx[u] += 1;
        }
        else { // no more outEdge from node u, backtracking
            ans.pb(u);
            pilha.pop_back();
        }
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

int32_t main(){ sws;
    ll n, m; cin >> n >> m;

    // OBS: some nodes are isolated and don't contribute to the eulerian path
    ll participantNodes = 0;

    for(ll i=0; i<m; i++) {
        ll a, b; cin >> a >> b;

        g[a].pb(b);
        ug[a].pb(b); ug[b].pb(a);

        outDegree[a] += 1;
        inDegree[b] += 1;

        if (!vis[a]) {
            vis[a] = 1;
            participantNodes += 1; 
        }
        if (!vis[b]) {
            vis[b] = 1;
            participantNodes += 1; 
        }
    }

    if ( !checkPossiblePath(1, n, n, participantNodes) ) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    for(auto elem : hierholzer(1, n)) cout << elem << ' ';
    cout << endl;
}   
```

#### Example 2:

Generating an **Eulerian Circuit** with Hierholzer in an *Undirected Graph*, starting on node *1* and also ending on node *1*.

https://cses.fi/problemset/task/1691

```cpp
// adding log2(m) complexity due to ordered_set structure required for not using a same bidirectional edge twice
#include <bits/extc++.h>
using namespace __gnu_pbds;
template <class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

vector<ordered_set<ll>> g(MAX, ordered_set<ll>()); // undirected graph

vll degree(MAX, 0);

vector<bool> vis(MAX, 0);

ll dfsConnected(ll u) {
    ll total = 1; vis[u] = 1;
    for(auto v : g[u]) if (!vis[v]) {
        total += dfsConnected(v);
    }
    return total;
}

// O(n log2(m)) -> O(Vertices * log2(Edges))
bool checkPossiblePath(ll n, ll nodes) {

    // check connectivity
    vis.assign(n+1, 0);
    ll connectedNodes = dfsConnected(1);
    if (connectedNodes != nodes) return 0;

    // check degrees
    for(ll i=1; i<=n; i++) {
        // all degrees need to be even
        if (degree[i] % 2 == 1) return 0;
    }

    return 1;
}

// O(m * log2(m)) -> O(Edges * log2(m)) 
// Hierholzer function can be used directly if there is already a garanted existance of an eulerian path/circuit.
vll hierholzer(ll start, ll n) { // generate an eulerian path, assuming there is only 1 end node
    vll ans, pilha, idx(n+1, 0);

    pilha.pb(start);
    while(!pilha.empty()) {
        ll u = pilha.back();
        if (idx[u] < (ll) g[u].size()) {
            ll v = *(g[u].find_by_order(idx[u]));
            
            pilha.pb( v );
            g[v].erase(u);

            idx[u] += 1;
        }
        else { // no more outEdge from node u, backtracking
            ans.pb(u);
            pilha.pop_back();
        }
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

int32_t main(){ sws;
    ll n, m; cin >> n >> m;

    // OBS: some nodes are isolated and don't contribute to the eulerian circuit
    ll participantNodes = 0;

    for(ll i=0; i<m; i++) {
        ll a, b; cin >> a >> b;

        g[a].insert(b);
        g[b].insert(a);

        degree[a] += 1;
        degree[b] += 1;

        if (!vis[a]) {
            vis[a] = 1;
            participantNodes += 1; 
        }
        if (!vis[b]) {
            vis[b] = 1;
            participantNodes += 1; 
        }
    }

    if ( !checkPossiblePath(n, participantNodes) ) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    for(auto elem : hierholzer(1, n)) cout << elem << ' ';
    cout << endl;
}   
```
