/**
 * Author: Wallace
 * Date: 04/02/2024
 * Description: After finding bridges, set an component id for each vertice, 
 * then merge vertices that are in the same 2-edge connected component
 * Time: O(V+E)
 */

// g: u -> {v, edge id}
vector<vector<pll>> g(MAX);
vector<vll> gc(MAX);
ll timer = 1;
ll tin[MAX], low[MAX], comp[MAX];
bool isBridge[MAX];

void dfs(ll u, ll p = -1) {
    tin[u] = low[u] = timer++;
    for(auto [v, id] : g[u]) if (v != p) {
        if (tin[v])
            low[u] = min(low[u], tin[v]); 
        else {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > tin[u])
                isBridge[id] = 1;
        }   
    }
}

void dfs2(ll u, ll c, ll p = -1) {
    comp[u] = c;
    for(auto [v, id] : g[u]) if (v != p) {
        if (isBridge[id]) continue;
        if (!comp[v]) dfs2(v, c, u);
    }
}

void bridgeTree(ll n) {
    // find bridges
    for(ll i=1; i<=n; i++) if (!tin[i])
        dfs(i);

    // find components
    for(ll i=1; i<=n; i++) if (!comp[i]) 
        dfs2(i, i);

    // condensate into a TREE (or TREES if disconnected)
    for(ll u=1; u<=n; u++) {
        for(auto [v, id] : g[u]) {
            if (comp[u] != comp[v]) {
                gc[comp[u]].pb(comp[v]);
            }
        }
    }
}