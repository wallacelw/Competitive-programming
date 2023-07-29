## Center of Tree

**Eccentricity:** The eccentricity of a vertice is the maximum distance between this distance and any other one.

**Centers of the Tree:** A tree can be *central* or *bicentral*, containing, respectively, a center or a bicenter. 

A tree can have multiple diameters. 

But if the the diameter has an odd length, the center of all diameters is the same node. 

Likewise, if the diameter has even length, there are two adjacent nodes that are the bicenter of the tree.

#### Algorithm for finding Center(s)

Remove leaves with a queue until there is one or two nodes.

```cpp
vector<vll> g(MAX);
ll degree[MAX];

vector<ll> find_center(ll n) {
    queue<pll> q; // {node, layer (0 == outer)}
    for(ll i=1; i<=n; i++) if (degree[i] == 1) q.push({i, 0});
    
    ll cnt = 0;

    while(!q.empty()) {
        if (cnt == n-2) {
            auto [nodeA, layerA] = q.front();
            auto [nodeB, layerB] = q.back();
            if (layerA == layerB) {
                return {nodeA, nodeB};
            }
        }

        if (cnt == n-1) {
            auto [node, layer] = q.front();
            return {node};
        }

        auto [u, l] = q.front(); q.pop();

        for(auto v : g[u]) {
            degree[v]--;
            if (degree[v] == 1) q.push({v, l+1}); 
        }

        cnt++;
    }

    return {};
}

int32_t main() { sws;
    ll n; cin >> n;
    for(ll i=0; i<n-1; i++) {
        ll a, b; cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
        degree[a]++, degree[b]++;
    }
    vll center = find_center(n);
    if (center.size() == 1) 
        cout << center[0] << endl;
    else
        cout << center[0] << " " << center[1] << endl;
}
```