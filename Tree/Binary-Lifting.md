## Binary lifting

**Solves**: LCA, O(log) travelling in a tree
**OBS:** log2(1e5) ~= 17; log2(1e9) ~= 30 ; log2(1e18) ~= 60
**Use for deep trees:** LLOGMAX = 62;

```cpp
struct BinaryLifting {
    ll n, logN = 20; // ~1e6
    vector<vll> g;
    vector<ll> depth;
    vector<vll> up;
 
    BinaryLifting(vector<vll> &g_)
     : g(g_), n(g_.size() + 1) { // 1-idx
        depth.assign(n, 0);
 
        while((1 << logN) < n) logN++;
        up.assign(n, vll(logN, 0));
        build();
    }
 
    void build(ll u = 1, ll p = -1) {
        for(ll i=1; i<logN; i++) {
            up[u][i] = up[ up[u][i-1] ][i-1];
        }
        
        for(auto v : g[u]) if (v != p) {
            up[v][0] = u;
            depth[v] = depth[u] + 1;
            build(v, u);
        }
    }
 
    ll go(ll u, ll dist) { // O(log(n))
        for(ll i=logN-1; i>=0; i--) { // bigger jumps first
            if (dist & (1LL << i)) {
                u = up[u][i];
            }
        }
        return u;
    }
 
    ll lca(ll a, ll b) { // O(log(n))
        if (depth[a] < depth[b]) swap(a, b);
        a = go(a, depth[a] - depth[b]);
        if (a == b) return a;
        
        for(ll i=logN-1; i>=0; i--) {
            if (up[a][i] != up[b][i]) {
                a = up[a][i];
                b = up[b][i];
            }
        }
        return up[a][0];
    }

    ll lca(ll a, ll b, ll root) { // lca(a, b) when tree is rooted at 'root'
        return lca(a, b)^lca(b, root)^lca(a, root); //magic
    }
};
```

## Query Tree

```cpp
// MaxwellTree - Query tree do Maxwell
// No update, Static tree
// Only Queries
struct BinaryLifting {
    ll n, logN = 20; // ~1e6
    vector<vpll> g;
    vector<ll> depth;
    vector<vll> up, mx, mn;

    BinaryLifting(vector<vpll> &g_)
     : g(g_), n(g_.size() + 1) { // 1-idx
        depth.assign(n, 0);

        while((1 << logN) < n) logN++;
        up.assign(n, vll(logN, 0));
        mx.assign(n, vll(logN, -INF));
        mn.assign(n, vll(logN, INF));
        build();
    }

    void build(ll u = 1, ll p = -1) {
        
        for(ll i=1; i<logN; i++) {
            mx[u][i] = max(mx[u][i-1], mx[ up[u][i-1] ][i-1]);
            mn[u][i] = min(mn[u][i-1], mn[ up[u][i-1] ][i-1]);
            up[u][i] = up[ up[u][i-1] ][i-1];
        }
        
        for(auto [v, w] : g[u]) if (v != p) {
            mx[v][0] = mn[v][0] = w;
            up[v][0] = u;
            depth[v] = depth[u] + 1;
            build(v, u);
        }
    }

    array<ll, 3> go(ll u, ll dist) { // O(log(n))
        ll mxval = -INF, mnval = INF;
        for(ll i=logN-1; i>=0; i--) { // bigger jumps first
            if (dist & (1LL << i)) {
                mxval = max(mxval, mx[u][i]);
                mnval = min(mnval, mn[u][i]);
                u = up[u][i];
            }
        }
        return {u, mxval, mnval};
    }

    array<ll, 3> query(ll u, ll v) { // O(log(n))
        if (depth[u] < depth[v]) swap(u, v);

        auto [a, mxval, mnval] = go(u, depth[u] - depth[v]);
        ll b = v;

        if (a == b) return {a, mxval, mnval};
        
        for(ll i=logN-1; i>=0; i--) {
            if (up[a][i] != up[b][i]) {
                mxval = max({mxval, mx[a][i], mx[b][i]});
                mnval = min({mnval, mn[a][i], mn[b][i]});
                a = up[a][i];
                b = up[b][i];
            }
        }

        mxval = max({mxval, mx[a][0], mx[b][0]});
        mnval = min({mnval, mn[a][0], mn[b][0]});
        return {up[a][0], mxval, mnval};
    }
};
```