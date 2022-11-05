## BFS

```cpp
vector<vll> g(MAX, vll());
queue<ll> fila;
bool visited[MAX];
ll d[MAX]; // distance

void bfs(ll i){
    memset(visited, 0, sizeof(visited));
    memset(distance, -1, sizeof(distance));
    fila.push(i);

    d[1] = 0; // 
    while(!fila.empty()){
        ll u = fila.front(); fila.pop();

        for(auto v : g[u]){
            if (visited[v]) continue;
            visited[v] = 1;
            d[v] = d[u] + 1;
            fila.push(v);
        }
    }
}
```