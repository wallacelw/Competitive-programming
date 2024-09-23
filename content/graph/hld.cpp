/** 
 * Author: Wallace, tiagosf00
 * Date: 22/09/2024
 * Description: Decompose tree into heavy paths
 * Time: O(\log^2(N)) for queries
 * Status: tested https://cses.fi/problemset/result/10594430/
 */

// 1-idx, import Segtree struct if using queries
struct HLD {
 
    vector<vector<ll>> g; // g[u][0] is the heavy child
    ll n, timer = 1;
    
    vector<ll> sz, parent, depth, head, tin, tout;
 
    Segtree &st;
 
    HLD(vector<vector<ll>> &g_, Segtree &st_) 
        : g(g_), n(g.size()), sz(n), parent(n), depth(n), head(n), tin(n), tout(n), st(st_) {
            dfs_sz(1);
            dfs_hld(1);
        }
 
    void dfs_sz(ll u, ll p = -1) {
        sz[u] = 1;
        for(auto &v : g[u]) if (v != p) {
            parent[v] = u, depth[v] = depth[u] + 1;
            dfs_sz(v, u);
            sz[u] += sz[v];
            if (sz[v] > sz[g[u][0]] or sz[g[u][0]] == p) swap(v, g[u][0]);
        }
    }
 
    void dfs_hld(ll u, ll p = -1) {
        tin[u] = timer++;
        for(auto v : g[u]) if (v != p) {
            head[v] = (v == g[u][0] ? head[u] : v);
            dfs_hld(v, u);
        }
        tout[u] = timer;
    }
 
    // get sum of path in O(log^2)
    Segtree::Node query_path(ll a, ll b) {
        if (tin[a] < tin[b]) swap(a, b);
        if (head[a] == head[b]) return st.query(tin[b], tin[a]);
        return st.merge(
            st.query(tin[head[a]], tin[a]),
            query_path(parent[head[a]], b)
        );
    }
};