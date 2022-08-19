# Tree Transversal - Pre order (childs -> node) / "Euler Tour" / Preorder time / DFS time 

Created an array that can have some properties like all child vetices are right after the node

```cpp
vector<vector<int>> g(MAX, vector<int>());
int timer = 1; // to make a 1-indexed array
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