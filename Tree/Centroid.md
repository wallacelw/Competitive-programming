## Find the Centroid of a Tree

A centroid of a tree is defined as a node such that when the tree is rooted
at it, no other nodes have a subtree of size greater than $\frac{N}{2}$.

We can find a centroid in a tree by starting at the root. Each step, loop through all of its children. If all of its children have subtree size less than or equal to $\frac{N}{2}$, then it is a centroid. Otherwise, move to the child with a subtree size that is more than $\frac{N}{2}$ and repeat until you find a centroid.

```cpp
vector<vll> g(MAX, vll());
vll subtreeSize(MAX, 1);
ll N; // <- initialize N = n !!

void getSizes(ll u = 1, ll p = -1) {
	for(auto v : g[u]) if (v != p) {
		getSizes(v, u);
		subtreeSize[u] += subtreeSize[v];
	}
}

ll centroid(ll u = 1, ll p = -1) {
	for(auto v : g[u]) if (v != p) {
		if (subtreeSize[v] * 2 > N) return centroid(v, u);
	}
	return u;
}
```