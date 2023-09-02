## Fluxo

**Complexity:** O( Vertices^2 * Edges)

- For unit capacity graph: O( (V+E) sqrt(E) )
- For unit capacity and also Bipartite Graphs: O( (V+E) sqrt(V) )

```cpp
const ll N = 505; // number of nodes, including sink and source

struct Dinic {
    struct Edge { 
        ll from, to, flow, cap;
    };
    vector<Edge> edges;

    vector<ll> g[N];
    ll ne = 0, lvl[N], vis[N], pass;
    ll qu[N], px[N], qt;

    ll run(ll s, ll sink, ll minE) {
        if (s == sink) return minE;
        ll ans = 0;
        for(; px[s] < (int)g[s].size(); px[s]++){
            ll e = g[s][ px[s] ];
            auto &v = edges[e], &rev = edges[e^1];
            if( lvl[v.to] != lvl[s]+1 || v.flow >= v.cap) continue;
            ll tmp = run(v.to, sink, min(minE, v.cap - v.flow));
            v.flow += tmp, rev.flow -= tmp;
            ans += tmp, minE -= tmp;
            if (minE == 0) break;
        }
        return ans;
    }

    bool bfs(ll source, ll sink) {
        qt = 0;
        qu[qt++] = source;
        lvl[source] = 1;
        vis[source] = ++pass;
        for(ll i=0; i<qt; i++) {
            ll u = qu[i];
            px[u] = 0;
            if (u == sink) return 1;
            for(auto& ed :g[u]) {
                auto v = edges[ed];
                if (v.flow >= v.cap || vis[v.to] == pass) continue;
                vis[v.to] = pass;
                lvl[v.to] = lvl[u]+1;
                qu[qt++] = v.to;
            }
        }
        return false;
    }

    ll flow(ll source, ll sink) { // max_flow
        reset_flow();
        ll ans = 0;
        while(bfs(source, sink))
            ans += run(source, sink, LLINF);
        return ans;
    }

    void addEdge(ll u, ll v, ll c, ll rc = 0) { // c = capacity, rc = retro-capacity;
        Edge e = {u, v, 0, c};
        edges.pb(e);
        g[u].pb(ne++);
        e = {v, u, 0, rc};
        edges.pb(e);
        g[v].pb(ne++);
    }

    void reset_flow() {
        for (ll i=0; i<ne; i++) edges[i].flow = 0;
        memset(lvl, 0, sizeof(lvl));
        memset(vis, 0, sizeof(vis));
        memset(qu, 0, sizeof(qu));
        memset(px, 0, sizeof(px));
        qt = 0; pass = 0;
    }

    vector<pll> cut() { // OBS: cut set cost is equal to max flow (number of edges)
        // the cut set is the set of edges that, if removed, will disrupt flow and make it 0.
        vector<pll> cuts;
        for (auto [from, to, flow, cap]: edges)
            if (flow == cap and vis[from] == pass and vis[to] < pass and cap > 0)
                cuts.pb({from, to});
        return cuts;
    }
};
```

#### How to use?

Set an unique id for all nodes

Remember to include the sink vertex and the source vertex. Usually *n+1* and *n+2*, *n* = max number of normal vertices

use **dinic.addEdge** to add edges -> (from, to, normal way capacity, retro-capacity)

use **dinic.flow(source_id, sink_id)** to receive maximum flow from source to sink through the network

### Minimum Cut

Another problem solved by network flow is the **minimum cut**.

Let’s define an **s-t cut C** = *(S-component, T-component)* as a partition of *V ∈ G* such that source *s ∈ S-component* and sink *t ∈ T-component*. Let’s also define a cut-set of C to be the set {(u, v) ∈ E | u ∈ S-component, v ∈ T-component} such that if all edges in the cut-set of C are removed, the Max Flow from s to t is 0 (i.e., s and t are disconnected). The cost of an s-t cut C is defined by the sum of the capacities of the edges in the cut-set of C.

The by-product of computing Max Flow is Min Cut! After Max Flow algorithm stops, we run graph traversal (DFS/BFS) from source s again. All reachable vertices from source s using positive weighted edges in the residual graph belong to the S-component. All other unreachable vertices belong to the T-component. All edges connecting the S-component to the T-component belong to the cut-set of C. The Min Cut value is equal to the Max Flow value mf. This is the minimum over all possible s-t cuts values.

#### Example:

https://cses.fi/problemset/task/1695/

```cpp
int32_t main(){ sws;
    ll n, m; cin >> n >> m;
    Dinic dinic;
    for(ll i=0; i<m; i++) {
        ll u, v; cin >> u >> v;
        dinic.addEdge(u, v, 1, 1);
    }
    dinic.flow(1, n);
    vpll ans = dinic.cut();
    cout << ans.size() << endl;
    for(auto [u, v] : ans) cout << u << ' ' << v << endl;
}   
```

### Matching

A perfect matching includes all vertices from the bipartite graph L and R. 

A maximum matching has the maximum cadinality. A perfect matching is a maximum matching. But the opposite is not necessarity true.

It's possible to access *dinic.edges*, which is a vector that contains all edges and also its respective attributes, like the .flow passing through each edge. Remember to consider that negative flow exist for reverse edges. 

This can be used to **matching problems** with a bipartite graph and *1 capacity* for example.