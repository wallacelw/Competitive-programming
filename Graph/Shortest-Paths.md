## Single-Source Shortest Paths (SSSP)

### Bellman-Ford for shortest paths

**Supports** Negative edges!

**Solves:** Finds all shortest paths from a initial node *x* to every other node

**Complexity:** O(n * m) = O(vertices * edges) -> O(n^2) "quadratic"

**Conjecture:** After **at most** *n-1 (Vertices-1) iterations*, all shortest paths will be found.

```cpp
#define tlll tuple<ll, ll, ll>
vector<tlll> edges(MAX, tlll() );
vll d(MAX, INF);

void BellmanFord(ll x, ll n) {
    d[x] = 0;
    for(ll i=0; i<n-1; i++) { // n-1 iterations will suffice 
        for(auto [u, v, w] : edges) if (d[u] + w < d[v]) {
              d[v] = d[u] + w;
        }
    }
}
```

#### Variation of Bellman-Ford to find a negative cycle

Iterate *n* (number of Vertices) times and if in the last iteration a distance if reduced, it means that there is a negative cycle.
Save this last node, whose distance was reduced, and, which a parent array, reconstruct the negative cycle.

```cpp
#define tlll tuple<ll, ll, ll>
vector<tlll> edges;
vll d(5050, INF);
vll p(5050, -1);

// modification of bellman-ford algorithm to detect negative cycle
void BellmanFord_Cycle(ll start, ll n){ // O (Vertices * Edges)
    d[start] = 0;
    ll x = -1; // possible node inside a negative cycle

    for(ll i=0; i<n; i++) { // n-iterations to find a cycle in the last iteration
        x = -1; // default value 
        for(auto [u, v, w] : edges) if (d[u] + w < d[v]) {
            d[v] = d[u] + w;
            p[v] = u;
            x = v;
        }
    }

    if (x != -1) { // Negative cycle found
        for(ll i=0; i<n; i++) x = p[x]; // set x to a node, contained in a cycle in p[]

        vll cycle = {x};
        for(ll tmp = p[x]; tmp != x; tmp = p[tmp]) cycle.pb(tmp);
        cycle.pb(x);
        reverse(cycle.begin(), cycle.end());

        //output 
        for(auto elem : cycle) cout << elem << ' ';
        cout << endl;
        return;
    } 
    // No Negative cycles
    return;
}
```

### Dijkstra

**Only Works for Non-Negative Weighted Graph**

**Complexity:** O((V+E)log(V)) -> O(n log n) 
```cpp
priority_queue<pll, vpll, greater<pll>> pq;
vector<vpll> g(MAX, vpll());
vll d(MAX, INF);

void dijkstra(ll start){
    pq.push({0, start});
    d[start] = 0;

    while( !pq.empty() ){
        auto [p1, u] = pq.top(); pq.pop();
        if (p1 > d[u]) continue;
        for(auto [v, p2] : g[u]){
            if (d[u] + p2 < d[v]){
                d[v] = d[u] + p2;
                pq.push({d[v], v});
            }
        }
    }
}
```

**OBS** Dijkstra can be modified for the opposite operation: *longest paths*.

### Modified Dijkstra for K-Shortest Paths

```cpp
priority_queue<pll, vpll, greater<pll>> pq;
vector<vpll> g(MAX, vpll());
vll cnt(MAX, 0);

// modified Dijkstra for K-Shortest Paths (not necessarily the same distance)
vll dijkstraKSP(ll start, ll end, ll k){ // O(K * M) = O(K * Edges) 

    vll ans;
    pq.push({0, start});

    while( cnt[end] < k ){
        auto [dis, u] = pq.top(); pq.pop();

        if (cnt[u] == k) continue;
        cnt[u] += 1;

        if (u == end) { // found a shortest path 
            ans.pb(dis); // adding the distance of this path
        }

        for(auto [v, w] : g[u]){
            pq.push({dis+w, v});
        }
    }

    return ans; // not ordered!
}
```

#### Extended Dijkstra

Besides the **Shortest Path Distance**, 

Also *Computes*: 

- **how many shortest paths**;
- **what is the minimum number of edges transversed in any shortest path**;
- **what is the maximum number of edges transversed in any shortest path**;

https://cses.fi/problemset/task/1202

```cpp
priority_queue<pll, vector<pll>, greater<pll>> pq;
vector<vpll> g(MAX, vpll());
vll d(MAX, LLINF);
vll ways(MAX, 0);
vll mn(MAX, LLINF);
vll mx(MAX, -LLINF);

void dijkstra(ll start){
    pq.push({0, start});

    ways[start] = 1;
    d[start] = 0, mn[start] = 0, mx[start] = 0;

    while( !pq.empty() ){
        auto [p1, u] = pq.top(); pq.pop();

        if (p1 > d[u]) continue;

        for(auto [v, p2] : g[u]){
            // reset info, shorter path found, previous ones are discarted
            if (d[u] + p2 < d[v]){ 

                ways[v] = ways[u];
                mn[v] = mn[u]+1;
                mx[v] = mx[u]+1;
                d[v] = d[u] + p2;

                pq.push({d[v], v});

            }
            // same distance, another path, update info
            else if (d[u] + p2 == d[v]) { 
                ways[v] = (ways[v] + ways[u]) % MOD;
                mn[v] = min(mn[v], mn[u]+1);
                mx[v] = max(mx[v], mx[u]+1);
            }
        }
    }
}
```

## All-Pairs Shortest Paths (APSP)

### Floyd Warshall

**Complexity:** O(V^3)

TODO