/**
 * Author: Wallace
 * Date: 06/02/2024
 * Description: Sort all edges in crescent order by weight, 
 * include all edges which joins two disconnected trees. In case of tie, choose whichever. 
 * Dont include edges that will join a already connected part of the tree.
 * Time: O(E \log{E} \alpha )
 */

// use DSU struct
struct DSU{};

set<array<ll, 3>> edges;

int32_t main(){ sws;
    ll n, m; cin >> n >> m;
    DSU dsu(n+1);
    for(ll i=0; i<m; i++) {
        ll u, v, w; cin >> u >> v >> w;
        edges.insert({w, u, v});
    }
    ll minCost = 0;
    for(auto [w, u, v] : edges) {
        if (dsu.find(u) != dsu.find(v)) {
            dsu.join(u, v);
            minCost += w;
        }
    }
    cout << minCost << endl;
}