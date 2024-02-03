## Centroid

A centroid of a tree is defined as a node such that when the tree is rooted
at it, no other nodes have a subtree of size greater than *N/2*.

We can find a centroid in a tree by starting at the root. Each step, loop through all of its children. If all of its children have subtree size less than or equal to *N/2*, then it is a centroid. Otherwise, move to the child with a subtree size that is more than *N/2* and repeat until you find a centroid.

**There is a centroid considering the leaves only (leaf centroid):** When the tree is rooted at the leaf centroid, no child subtree has a number of leaves greater than *N/2*.

**Find centroid:**
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


## Centroid Decomposition

```cpp
vi decomp[MAXN];
int st[MAXN];
int processed[MAXN];

int getCent(int v,int p,int tSize){
    for(auto c:adj[v]){
        if(c==p || processed[c])continue;
        if((st[c]<<1)>tSize)return getCent(c,v,tSize);
    }
    return v;
}


int getSubtreeSize(int v,int p =-1){
    st[v]=1;
    for(auto c:adj[v]){
        if(c==p || processed[c])continue;
        getSubtreeSize(c,v);
        st[v]+=st[c];
    }
    return st[v];
}


int build_cent(int v){
    int cent = getCent(v,-1,getSubtreeSize(v));

    processed[cent]=true;

    for(auto c:adj[cent]){
        if(processed[c])continue;   
        int nx = build_cent(c);
        decomp[nx].pb(cent);
        decomp[cent].pb(nx);
    }
    return cent;

}
```