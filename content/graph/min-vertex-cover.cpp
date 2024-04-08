/** 
 * Author: Wallace
 * Date: 07/04/2024
 * Description: computes the min vertex cover for a bipartite graph matched with dinitz
 * Time: O(E log(E))
 * Status: tested (https://cses.fi/problemset/result/8952576/)
 */


// a vertex cover is a set of vertices that contains
// at least one endpoint for each edge in the bipartite match
// A vertex cover in minimum if no other vertex cover has fewer vertices.
// only for bipartite graphs
vector<ll> minVertexCover(Dinitz &dinitz) {
    ll n = dinitz.n;

    vector<vector<ll>> g(n);
    set<ll> left, right; // unique
    vector<bool> matched(n);

    for(auto e : dinitz.edges) {
        if (e.u == dinitz.src or e.u == dinitz.sink) continue;
        if (e.v == dinitz.src or e.v == dinitz.sink) continue;
        if (e.cap > 0) { // not retro edge

            left.insert(e.u);
            right.insert(e.v);

            if (e.flow == e.cap) {
                // orient matched edges from right to left
                g[e.v].pb(e.u);
                matched[e.u] = 1;
                matched[e.v] = 1;
            }
            else {
                // orient non-matched edges from left to right
                g[e.u].pb(e.v);
            }
        }
    };

    vector<bool> vis(n, 0);
    function<void (ll)> dfs = [&](ll u) {
        vis[u] = 1;
        for(auto v : g[u]) 
            if (!vis[v]) 
                dfs(v);
    };

    for(auto l : left) if (!matched[l]) {
        dfs(l);
    }

    vector<ll> ans;
    for(auto l : left) if (!vis[l]) {
        ans.pb(l);
    }
    for(auto r : right) if (vis[r]) {
        ans.pb(r);
    }

    // remember, right nodes ids are dislocated by an offset
    return ans;
}