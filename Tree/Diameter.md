## Find the Diameter

From any node X find a node A which is the farthest away from X.
Then, from node A, find a node B which is the farthest away from A. 

Path from (A - B) is a diameter.

It can be proven by drawing a diameter line. If any node is further than any of the diameter extremities, then it should be switched (so the first line wasn't a diameter at all).

From any node, the fasthest node is a diameter extremity. Then from this extremity, the fasthest node is the other diameter extremity.

```cpp
vector<vll> g(MAX, vll());
 
pll dfs(ll u, ll p){
    pll ans = {u, 0};
    for(auto v : g[u]) if (v != p) {
        auto [node, comp] = dfs(v, u);
        if (comp+1 > ans.ss){
            ans = {node, comp+1};
        }
    }
    return ans;
}
 
int32_t main(){sws;
    ll n; cin >> n;
    for(ll i=1; i<n; i++){
        ll a, b; cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
    }
    ll ans1 = dfs(1, 1).ff;
    cout << dfs(ans1 , ans1).ss << endl;
}
```

### Find the lenght of the longest path from all nodes

It can be proven that to any node X, the maximum distance is either dist(X, A) or dist(X, B), which are the extremities of a diameter.

```cpp
vector<vll> g(MAX, vll());
vll distA(MAX, 0);
vll distB(MAX, 0);

pll dfs(ll u, ll p, ll op) {
    pll ans = {u, 0};
    for(auto v : g[u]) if (v != p) {
        if (op == 1) distA[v] = distA[u]+1;
        else if (op == 2) distB[v] = distB[u]+1;

        auto [node, length] = dfs(v, u, op);
        
        if (length + 1 > ans.ss)
            ans = {node, length+1};
    }
    return ans;
}

int32_t main() { sws;
    ll n; cin >> n;
    for(ll i=0; i<n-1; i++) {
        ll u, v; cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }

    auto [nodeA, _t1] = dfs(1, -1, 0);
    auto [nodeB, _t2] = dfs(nodeA, -1, 1);
    dfs(nodeB, -1, 2);

    for(ll i=1; i<=n; i++) {
        cout << max(distA[i], distB[i]) << ' '; 
    }
    cout << endl;
}   
```