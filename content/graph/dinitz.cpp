/** 
 * Author: Wallace, Quirino
 * Date: 07/04/2024
 * Description: This second version may be slower due to dynamic allocation, queue, etc
 * but it's more readable, more memory efficient
 * Time: General Case, O(V^2 E); 
 * Unit Capacity, O((V+E) \sqrt{E});
 * Bipartite and unit capacity, O( (V+E) \sqrt{V})
 * Status: tested! https://www.spoj.com/submit/FASTFLOW/, 0.37s, 
 * slow for plug it in
 * min cut tested(police chase): https://cses.fi/problemset/result/8951521/
 */

struct Dinitz {
    struct Edge { // u -> v
        ll u, v, cap, flow=0; // u is redundant, but nice for some problems
    };

    vector<Edge> edges;
    vector<vector<ll>> g;
    vector<ll> level, ptr;

    // n need to be big enough for all nodes, including src/sink
    ll n, src, sink;
    Dinitz(ll n_, ll s = -1, ll t = -1) : n(n_+10) {
        src = (s == -1 ? n-2 : s);
        sink = (t == -1 ? n-1 : t);
        g.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void addEdge(ll u, ll v, ll cap, ll rcap = 0) { // rcap = retrocapacity for bidiretional edges
        g[u].push_back( (ll)edges.size() );
        edges.push_back({u, v, cap});
        g[v].push_back( (ll)edges.size() );
        edges.push_back({v, u, rcap});
    }

    
    bool bfs() {
        for(ll i=0; i<n; i++) level[i] = -1; // not vis
        level[src] = 0;
        queue<ll> q;
        q.push(src);
        while (!q.empty()) {
            ll u = q.front(); q.pop();
            for (auto eid : g[u]) {
                auto e = edges[eid];
                if (e.flow >= e.cap or level[e.v] != -1) continue;
                level[e.v] = level[u] + 1;
                q.push(e.v);
            }
        }
        return level[sink] != -1;
    }

    ll dfs(ll u, ll f) {
        if (f == 0 or u == sink) return f;
        for (ll &i = ptr[u]; i < (ll)g[u].size(); i++) {
            ll eid = g[u][i];
            auto &e = edges[eid];
            if(e.flow >= e.cap or level[u]+1 != level[e.v]) continue;
            ll newf = dfs(e.v, min(f, e.cap - e.flow));
            if (newf == 0) continue;
            e.flow += newf;
            edges[eid^1].flow -= newf;
            return newf;
        }
        return 0;
    }

    ll max_flow = 0;
    ll flow(bool reset_flow = true) {
        if (reset_flow) {
            max_flow = 0;
            for(ll u=0; u<n; u++) {
                for(auto eid : g[u]) {
                    auto &e = edges[eid];
                    e.flow = 0;
                }
            }
        }
        while (bfs()) {
            for(ll i=0; i<n; i++) ptr[i] = 0;
            while (ll newf = dfs(src, INF))
                max_flow += newf;
        }
        return max_flow;
    }

    // minimum cut set cost = minimum cost = max flow
    // minimum cut set is the minimum set of edges that, if removed, 
    // will disrupt flow from source to sink and make it 0.
    vector<pll> cut() {
        vector<pll> cuts;
        for (auto [u, v, cap, flow]: edges) {
            if (level[u] != -1 and level[v] == -1) {
                cuts.pb({u, v});
            }
        }
        return cuts;
    }
};