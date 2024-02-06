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

    Kosaraju(vector<vll> &g_) 
      : g(g_), n(g_.size()-1) { // 1-idx

        gi.assign(n+1, vll());
        for(ll i=1; i<=n; i++) {
            for(auto j : g[i])
                gi[j].pb(i);
        }

        gc.assign(n+1, vll());
        vis.assign(n+1, 0);
        comp.assign(n+1, -1);
        st = stack<ll, vll>();

        for(ll i=1; i<=n; i++) if (!vis[i]) dfs(i);

        while(!st.empty()) {
            auto u = st.top(); st.pop();
            if (comp[u] == -1) dfs2(u, u);
        }

        for(ll u=1; u<=n; u++)
            for(auto v : g[u])
                if (comp[u] != comp[v]) 
                    gc[comp[u]].pb(comp[v]);
    }
};