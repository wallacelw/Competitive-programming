/**
 * Author: Wallace
 * Date: 03/02/2024
 * Description: Solves LCA for trees
 * Time: $O(N \log(N))$ to build, $O(\log(N))$ per query
 */

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
        return lca(a, b)^lca(b, root)^lca(a, root); // magic
    }
};