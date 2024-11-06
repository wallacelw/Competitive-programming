/** 
 * Author: Wallace, tiagosf00
 * Date: 23/09/2024
 * Description: Decompose tree into heavy paths
 * Time: O(\log^2(N)) for queries (log paths in tree and log due to the seg)
 * Status: tested https://cses.fi/problemset/result/10602688/
 */

struct HLD {
    vector<vector<ll>> &g; // g[u][0] is the heavy child
    ll n, timer = 1;

    vector<ll> sz, parent, depth, head, tail, tin, tout, inv; // inv = invert tin
 
    HLD(vector<vector<ll>> &g_) 
        : g(g_), n(g.size()), sz(n), parent(n), depth(n), head(n), tail(n), tin(n), tout(n), inv(n) {
            iota(head.begin(), head.end(), 0);
            dfs_sz(1);
            dfs_hld(1);
        }
 
    void dfs_sz(ll u, ll p = -1) {
        sz[u] = 1;
        for(auto &v : g[u]) if (v != p) {
            parent[v] = u, depth[v] = depth[u] + 1;
            dfs_sz(v, u);
            sz[u] += sz[v];
            if (sz[v] > sz[g[u][0]] or g[u][0] == p) swap(v, g[u][0]);
        }
    }
 
    void dfs_hld(ll u, ll p = -1) {
        inv[timer] = tail[u] = u;
        tin[u] = timer++;
        for(auto v : g[u]) if (v != p) {
            if (v == g[u][0]) head[v] = head[u];
            dfs_hld(v, u);
        }
        tout[u] = timer;
        if(g[u].size() > 1) tail[u] = tail[g[u][0]];
    }

    // 1-idx, import Segtree struct if using queries
    Segtree::Node query_path(ll a, ll b, Segtree &st) {
        if (tin[a] < tin[b]) swap(a, b);
        if (head[a] == head[b]) return st.query(tin[b], tin[a]);
        return st.merge(
            st.query(tin[head[a]], tin[a]),
            query_path(parent[head[a]], b, st)
        );
    }
};
