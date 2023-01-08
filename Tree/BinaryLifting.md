## Binary lifting

**Solves**: LCA, O(log) travelling in a tree

**OBS:** log2(1e5) ~= 17; log2(1e9) ~= 30 ; log2(1e18) ~= 60

**Use for deep trees:** LLOGMAX = 62;

```cpp
const ll LOGMAX = 32;

vector<vll> g(MAX, vll());
ll depth[MAX]; // depth[1] = 0 
ll jump[MAX][LOGMAX]; // jump[v][k] -> 2^k antecessor of v
// 1 points to 0 and 0 is the end point loop
ll N; // quantity of vertices of the tree

void binary_lifting(ll u = 1, ll p = -1){ // DFS, O(N)
    for(auto v : g[u]) if (v != p){
        depth[v] = depth[u] + 1;
        
        jump[v][0] = u;
        for(ll k=1; k < LOGMAX; k++)
            jump[v][k] = jump[ jump[v][k-1] ][k-1];
        binary_lifting(v, u);
    }
}

ll go(ll v, ll dist){ // O(log(N))
    for(ll k = LOGMAX-1; k >= 0; k--)
        if (dist & (1 << k))
            v = jump[v][k];
    return v;
}

ll lca(ll a, ll b){  // O(log(N))
    if (depth[a] < depth[b]) swap(a, b);
    
    a = go(a, depth[a] - depth[b]);
    if (a == b) return a;

    for(ll k = LOGMAX-1; k >= 0; k--){
        if (jump[a][k] != jump[b][k]){
            a = jump[a][k];
            b = jump[b][k];
        }
    }
    return jump[a][0];
}


int32_t main(){ sws;
    ll n; cin >> n;
    N = n;

    binary_lifting();
}
```