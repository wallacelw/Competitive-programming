/** 
 * Author: Wallace
 * Date: 05/02/2024
 * Description: By using the fact that the inverted graph has the same
 * SCCs, just do a DFS twice to find all SCCs. A condensated graph can be created
 * if wished. The condensated graph is a DAG!!
 * Time: O(V + E)
 * Status: Tested by Accepted (https://cses.fi/problemset/result/8395110/)
 */

struct Kosaraju {
    ll n;
    vector<vll> g, gi, gc;
    vector<bool> vis;
    vector<ll> comp;
    stack<ll, vll> st;

    void dfs(ll u) { // g
        vis[u] = 1;
        for(auto v : g[u]) if (!vis[v]) dfs(v);
        st.push(u);
    }

    void dfs2(ll u, ll c) { // gi
        comp[u] = c;
        for(auto v : gi[u]) if (comp[v] == -1) dfs2(v, c);
    }

    Kosaraju(vector<vll> &g_) : n(g_.size()-1), g(g_),
        gi(n+1), gc(n+1), vis(n+1, 0), comp(n+1, -1), st() { // 1-idx

        for(ll u=1; u<=n; u++) {
            for(auto v : g[u]) {
                gi[v].pb(u);
            }
        }

        for(ll i=1; i<=n; i++) if (!vis[i]) dfs(i);

        while(!st.empty()) {
            auto u = st.top(); st.pop();
            if (comp[u] == -1) dfs2(u, u);
        }

        for(ll u=1; u<=n; u++) {
            for(auto v : g[u]) {
                if (comp[u] != comp[v]) {
                    gc[comp[u]].pb(comp[v]);
                }
            }
        }
    }
};
