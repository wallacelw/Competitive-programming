/** 
 * Author: Quirino, Wallace
 * Date: 07/04/2024
 * Description: change bfs to spfa to attribute a weight for the edges
 * Time: SPFA is O(E) at average and O(V E) in the worst case 
 * Status: tested https://cses.fi/problemset/result/8951841/
 */

struct Dinitz {
    struct Edge { // u -> v
        ll u, v, cost, cap, flow=0;
    };

    vector<Edge> edges;
    vector<vector<ll>> g;
    vector<ll> dist, ptr; // uses dist instead of level

    // n need to be big enough for all nodes, including src/sink
    ll n, src, sink;
    Dinitz(ll nn, ll s = -1, ll t = -1) : n(nn+10) {
        src = (s == -1 ? n-2 : s);
        sink = (t == -1 ? n-1 : t);
        g.resize(n);
    }

    void addEdge(ll u, ll v, ll cost, ll cap, ll rcap = 0) { // rcap = retrocapacity for bidiretional edges
        g[u].push_back( (ll)edges.size() );
        edges.push_back({u, v, cost, cap});
        g[v].push_back( (ll)edges.size() );
        edges.push_back({v, u, -cost, rcap});
    }

    bool spfa() {
        dist.assign(n, INF);
        vector<bool> inqueue(n, false);

        queue<ll> q; q.push(src);
        dist[src] = 0;
        inqueue[src] = true;

        while (!q.empty()) {
            ll u = q.front(); q.pop();
            inqueue[u] = false;

            for (auto eid : g[u]) {
                auto const& e = edges[eid];
                if (e.flow >= e.cap) continue;
                if (dist[e.u] + e.cost < dist[e.v]) {
                    dist[e.v] = dist[e.u] + e.cost;
                    if (!inqueue[e.v]) {
                        q.push(e.v);
                        inqueue[e.v] = true;
                    }
                }
            }
        }
        return dist[sink] != INF;
    }

    ll min_cost = 0;
    ll dfs(ll u, ll f) {
        if (f == 0 or u == sink) return f;
        for (ll &i = ptr[u]; i < (ll)g[u].size();) {
            ll eid = g[u][i++];
            auto &e = edges[eid];
            if(e.flow >= e.cap or (dist[e.u] + e.cost) != dist[e.v]) continue;
            ll newf = dfs(e.v, min(f, e.cap - e.flow));
            if (newf == 0) continue;
            e.flow += newf;
            edges[eid^1].flow -= newf;
            min_cost += e.cost * newf;
            return newf;
        }
        return 0;
    }

    ll max_flow = 0;
    pair<ll, ll> flow(bool reset_flow_cost = true) {
        if (reset_flow_cost) {
            max_flow = 0;
            min_cost = 0;
            for(ll u=0; u<n; u++) {
                for(auto eid : g[u]) {
                    auto &e = edges[eid];
                    e.flow = 0;
                }
            }
        }
        while (spfa()) {
            ptr.assign(n, 0);
            while (ll newf = dfs(src, INF))
                max_flow += newf;
        }
        return {min_cost, max_flow};
    }
};