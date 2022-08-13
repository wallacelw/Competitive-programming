# Grafos

## DFS Tree

```cpp
bool visited[MAX];
vector<vll> g(MAX, vll());
map<ll, ll> spanEdges;
map<ll, ll> backEdges; // children to parent
ll h[MAX];
ll p[MAX];

void dfs(ll u=1, ll parent=0, ll layer=1){
    if (visited[u]) return;
    visited[u] = 1;
    h[u] = layer;
    for(auto v : g[u]){
        if (v == parent) spanEdges[u] = v;
        else if (visited[v] and h[v] < h[u]) backEdges[u] = v; 
        else dfs(v, u, layer+1);
    }
}
```

## Djikstra

```cpp
priority_queue<pll, vpll, greater<pll>> pq;
vector<vpll> g(MAX, vpll());
vll d(MAX, INF);

void dijkstra(ll start){
    pq.push({0, start});
    d[start] = 0;

    while( !pq.empty() ){
        ll u, p1; tie(p1, u) = pq.top(); pq.pop();
        if (p1 > d[u]) continue;
        for(auto elem : g[u]){
            ll v, p2; tie(v, p2) = elem;
            if (d[u] + p2 < d[v]){
                d[v] = d[u] + p2;
                pq.push({d[v], v});
            }
        }
    }
}
```

## BFS

### Global scope

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
```

### Main scope

```cpp
memset(visited, 0, sizeof(visited));
memset(distance, -1, sizeof(distance));

d[1] = 0;
fila.push(1);
```

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

# Tree Transversal - Pre order (childs -> node) / "Euler Tour" / Preorder time / DFS time 

Created an array that can have some properties like all child vetices are right after the node

```cpp
vector<vector<int>> g(MAX, vector<int>());
int timer = 0;
int st[MAX]; // L index
int en[MAX]; // R index

void dfs_time(int u, int p) {
	st[u] = timer++;
	for (int v : g[u]) if (v != p) {
        dfs_time(v, u);
	}
	en[u] = timer-1;
}
```

## Problems

https://cses.fi/problemset/task/1138 -> change value of node and calculate sum of the path to root of a tree