/** 
 * Author: Wallace, Quirino
 * Date: 06/06/2024
 * Description: Check existence conditions and produce path if possible
 * Time: O(E)
 * Status: Tested in CSES, cf(https://codeforces.com/contest/1981/my)
 */

// Euler Circuit - Undirected Graph (1-idx)
pair<bool, vector<ll>> circuit(ll n, vector<pll> &edges, ll src = 1) { 
    ll m = edges.size();
    vector<vector<pll>> g(n+1);
    
    for(ll i=0; i<m; i++) {
        auto [a, b] = edges[i]; 
        g[a].pb({b, i});
        g[b].pb({a, i});
    }

    // check for even degree
    for(ll i=0; i<=n; i++) {
        if (g[i].size() % 2) return {false, {}};
    }

    vector<ll> ans;
    vector<bool> vis(m, 0);
    function<void (ll)> dfs = [&](ll u) {
        while(g[u].size()) {
            auto [v, idx] = g[u].back();
            g[u].pop_back();
            if (vis[idx]) continue;
            vis[idx] = 1;
            dfs(v);
        }
        ans.pb(u);
    };
    dfs(src);

    // check for connectivity
    if (ans.size() != m + 1) return {false, {}};

    return {true, ans};
}

// Euler Path - Undirected Graph (1-idx)
pair<bool, vector<ll>> path(ll n, vector<pll> &edges, ll src, ll dst) { 
    ll m = edges.size();
    vector<vector<pll>> g(n+1);
    
    for(ll i=0; i<m; i++) {
        auto [a, b] = edges[i]; 
        g[a].pb({b, i});
        g[b].pb({a, i});
    }

    // check for even degree (except src and dst)
    for(ll i=0; i<=n; i++) {
        if (i == src or i == dst) continue;
        if (g[i].size() % 2) return {false, {}};
    }

    vector<ll> ans;
    vector<bool> vis(m, 0);
    function<void (ll)> dfs = [&](ll u) {
        while(g[u].size()) {
            auto [v, idx] = g[u].back();
            g[u].pop_back();
            if (vis[idx]) continue;
            vis[idx] = 1;
            dfs(v);
        }
        ans.pb(u);
    };
    dfs(src);

    // check for connectivity
    if (ans.size() != m + 1) return {false, {}};

    reverse(ans.begin(), ans.end());
    return {true, ans};
}

// Euler Path - Directed Graph (1-idx)
pair<bool, vector<ll>> path(ll n, vector<pll> &edges, ll src, ll dst) { 
    ll m = edges.size();
    vector<vector<ll>> g(n+1);
    
    vector<ll> in(n+1, 0), out(n+1, 0);
    for(auto [a, b] : edges) {
        g[a].pb(b);
        out[a]++, in[b]++;
    }

    // check for degrees
    for(ll i=0; i<=n; i++) {
        if (i == src or i == dst) continue;
        if (in[i] - out[i] != 0) return {false, {}};
    }
    if (out[src] != in[src] + 1) return {false, {}};
    if (in[dst] != out[dst] + 1) return {false, {}};

    vector<ll> ans;
    function<void (ll)> dfs = [&](ll u) {
        while(g[u].size()) {
            auto v = g[u].back();
            g[u].pop_back();
            dfs(v);
        }
        ans.pb(u);
    };
    dfs(src);

    // check for connectivity
    if (ans.size() != m + 1) return {false, {}};

    reverse(ans.begin(), ans.end());
    return {true, ans};
}