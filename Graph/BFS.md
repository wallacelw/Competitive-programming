## BFS

```cpp
vector<vll> g(MAX, vll());
queue<ll> fila;
bool vis[MAX];

void bfs(ll i){
    memset(vis, 0, sizeof(vis));
    fila.push(i);
    vis[i] = 1;
    
    while(!fila.empty()){
        ll u = fila.front(); fila.pop();

        for(auto v : g[u]) if (!vis[v]) {
            vis[v] = 1;

            d[v] = d[u] + 1;
            
            fila.push(v);
        }
    }
}
```