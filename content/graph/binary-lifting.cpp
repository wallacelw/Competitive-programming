/** 
 * Author: Wallace, Maxwell
 * Date: 03/02/2024
 * Description: Binary Lifting to compute the min, max edge weight
 * present in the simple path {a, lca(a, b), b} 
 * Time: $O(N \log(N))$ to build; $O(\log(N))$ per query
*/

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