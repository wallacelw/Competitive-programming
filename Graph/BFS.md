## BFS

```cpp
queue<ll> fila;
bool visited[MAX];
ll d[MAX]; // distance

void bfs(){
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

int32_t main(){sws;

    memset(visited, 0, sizeof(visited));
    memset(distance, -1, sizeof(distance));
    d[1] = 0;
    fila.push(1);
}
```