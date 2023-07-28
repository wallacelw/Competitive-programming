## Binary lifting

**Solves**: LCA, O(log) travelling in a tree

**OBS:** log2(1e5) ~= 17; log2(1e9) ~= 30 ; log2(1e18) ~= 60

**Use for deep trees:** LLOGMAX = 62;

```cpp
const int LOGMAX = 31; // 1e9
vector<vll> g(MAX);
ll depth[MAX], jump[MAX][LOGMAX];

void precompute(ll u=1, ll p=-1) { // DFS, O(n)
    for(auto v : g[u]) if (v != p) {
        depth[v] = depth[u] + 1;

        jump[v][0] = u;
        for(ll i=1; i<LOGMAX; i++)
            jump[v][i] = jump[ jump[v][i-1] ][i-1];

        precompute(v, u);
    }
}

ll go(ll u, ll dist) { // O(log(n))
    for(ll i=LOGMAX-1; i>=0; i--) // bigger jumps first
        if (dist & (1 << i))
            u = jump[u][i];

    return u;
}

ll lca(ll a, ll b) { // O(log(n))
    if (depth[a] < depth[b]) swap(a, b);
    a = go(a, depth[a] - depth[b]);
    if (a == b) return a;

    for (ll i=LOGMAX-1; i>=0; i--) {
        if (jump[a][i] != jump[b][i]) {
            a = jump[a][i];
            b = jump[b][i];
        }
    }

    return jump[a][0];
}

int32_t main(){ sws;
    precompute();
}
```