# DFS (elegant code)

## Weighted Edges

```cpp
vector<vpll> g(MAX, vpll());

void dfs(ll u, ll p = -1){
    for(auto [v, w] : g[u]) if (v != p){
        dfs(v, u);
    }
}
```