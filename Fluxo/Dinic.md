# Fluxo

```cpp
const ll N = MAX; // num vertices

struct Dinic {  // O( Vertices^2 * Edges)
    struct Edge { 
        ll from, to, flow, cap;
    };
    vector<Edge> edge;

    vll g[N];
    ll ne = 0, lvl[N], vis[N], pass;
    ll qu[N], px[N], qt;

    ll run(ll s, ll sink, ll minE) {
        if (s == sink) return minE;

        ll ans = 0;

        for(; px[s] < (int)g[s].size(); px[s]++){
            ll e = g[s][ px[s] ];
            auto &v = edge[e], &rev = edge[e^1];
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
                auto v = edge[ed];
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

    void addEdge(ll u, ll v, ll c, ll rc) { // c = capacity, rc = retro-capacity;
        Edge e = {u, v, 0, c};
        edge.pb(e);
        g[u].pb(ne++);

        e = {v, u, 0, rc};
        edge.pb(e);
        g[v].pb(ne++);
    }

    void reset_flow() {
        for (ll i=0; i<ne; i++) edge[i].flow = 0;
        memset(lvl, 0, sizeof(lvl));
        memset(vis, 0, sizeof(vis));
        memset(qu, 0, sizeof(qu));
        memset(px, 0, sizeof(px));
        qt = 0; pass = 0;
    }
};
```

### How to use?

Set an unique id for all nodes

Remember to include the sink vertex and the source vertex. Usually *n+1* and *n+2*, *n* = max number of normal vertices

use **dinic.addEdge** to add edges -> (from, to, normal way capacity, retro-capacity)

use **dinic.flow(source_id, sink_id)** to receive maximum flow from source to sink through the network

**OBS:** It's possible to access *dinic.edge*, which is a vector that contains all edges and also its respective properties, like the **flow** passing through each edge. This can be used to matching problems for example.

### Example

```cpp
int32_t main(){sws;
    ll n, m; cin >> n >> m;
    Dinic dinic;
 
    for(ll i=1; i<=n; i++){
        ll k; cin >> k;
        for(ll j=0; j<k; j++){
            ll empresa; cin >> empresa;
            empresa += n;
            dinic.addEdge(i, empresa, 1, 0);
        }
    }
 
    ll source = n + m + 1;
    ll sink = n + m + 2;
 
    for(ll i=1; i<=n; i++){
        dinic.addEdge(source, i, 1, 0);
    }
 
    for(ll j=1; j<=m; j++){
        dinic.addEdge(j+n, sink, 1, 0);
    }
 
    cout << m - dinic.flow(source, sink) << endl;
}
```