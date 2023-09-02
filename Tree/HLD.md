## Heavy Light Decomposition (WIP)

**Features:**

- Update all nodes along the path from node *x* to node *y*.

- Find the sum, maximum, minimum (or any other operation that satisfies the
associative property) along the path from node *x* to node *y*.

Each query takes *O(log(N))* time. So the total complexity should be *O(Q log(N))*

**Definitions:**

- A heavy child of a node is the child with the largest subtree size rooted at the child.
- A light child of a node is any child that is not a heavy child.
- A heavy edge connects a node to its heavy child.
- A light edge connects a node to any of its light children.
- A heavy path is the path formed by a collection heavy edges.
- A light path is the path formed by a collection light edges.

```cpp
ll N, v[MAX]; // Set N = n !
vector<vll> g(MAX, vll());

ll sz[MAX], p[MAX], dep[MAX], id[MAX], tp[MAX];
ll st[1 << 19];

void update_node(ll idx, ll val) { // O(log^2(N))
    st[idx += N] = val;
    for (idx /= 2; idx; idx /= 2)
        st[idx] = max(st[2 * idx], st[2 * idx + 1]);
}

ll query(ll lo, ll hi) {
    ll ra = 0, rb = 0;
    for (lo += N, hi += N + 1; lo < hi; lo /= 2, hi /= 2) {
        if (lo & 1)
            ra = max(ra, st[lo++]);
        if (hi & 1)
            rb = max(rb, st[--hi]);
    }
    return max(ra, rb);
}

ll dfs_sz(ll cur, ll par) {
    sz[cur] = 1;
    p[cur] = par;
    for(ll chi : g[cur]) {
        if(chi == par) continue;
        dep[chi] = dep[cur] + 1;
        p[chi] = cur;
        sz[cur] += dfs_sz(chi, cur);
    }
    return sz[cur];
}

ll ct = 1; // counter
void dfs_hld(ll cur, ll par, ll top) {
    id[cur] = ct++;
    tp[cur] = top;
    update_node(id[cur], v[cur]);
    ll h_chi = -1, h_sz = -1;
    for(ll chi : g[cur]) {
        if(chi == par) continue;
        if(sz[chi] > h_sz) {
            h_sz = sz[chi];
            h_chi = chi;
        }
    }
    if(h_chi == -1) return;
    dfs_hld(h_chi, cur, top);
    for(ll chi : g[cur]) {
        if(chi == par || chi == h_chi) continue;
        dfs_hld(chi, cur, chi);
    }
}

// returns the max_value of a node in the path from X to Y
ll path(ll x, ll y){ // O(log^2(N))
    ll ret = 0;
    while(tp[x] != tp[y]){
        if(dep[tp[x]] < dep[tp[y]])swap(x,y);
        ret = max(ret, query(id[tp[x]],id[x]));
        x = p[tp[x]];
    }
    if(dep[x] > dep[y])swap(x,y);
    ret = max(ret, query(id[x],id[y]));
    return ret;
}


int32_t main(){ sws;
    ll n, q; cin >> n >> q;
    N = n;
    for(ll i=1; i<=n; i++) cin >> v[i];
    for(ll i=2; i<=n; i++) {
        ll a, b; cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
    }
    dfs_sz(1, 1);
    dfs_hld(1, 1, 1);
    while(q--) {
        ll t; cin >> t;
        if (t == 1) {
            ll s, x; cin >> s >> x;
            v[s] = x;
            update_node(id[s], v[s]);
        }
        else {
            ll a, b; cin >> a >> b;
            cout << path(a, b) << endl;
        }
    }
}
```




## HLD Second Version
(Acelerado com binlift)
```cpp
vi adj[MAXN];
int up[MAXN][19];
int head[MAXN];
vi heavy(MAXN,-1);
int st[MAXN];
int id[MAXN];
int t[MAXN<<2];
int h[MAXN];
int val[MAXN];
int tin[MAXN];
int tout[MAXN];
int n,q;
int cur=0;
int temp=0;
 
int get(int a, int b) {
    a += n; b += n;
    int s = 0;
    while (a <= b) {
        if (a%2 == 1) s = max(s,t[a++]);
        if (b%2 == 0) s = max(s,t[b--]);
        a /= 2; b /= 2;
    }   
    return s; 
}

void update(int k, int x) {
    k += n;
    t[k] = x;
    for (k /= 2; k >= 1; k /= 2) {
        t[k] = max(t[2*k],t[2*k+1]);
    }
}

 
int dfs_sz(int v=1,int p=1,int he=0){
    // dbg("v_a",v)
    h[v]=he;
    up[v][0]=p;
    rep(i,1,19)up[v][i]=up[up[v][i-1]][i-1];
    int heavy_c=-1;
    int heavy_sz=0;
    tin[v]=temp++;
    st[v]=1;
    for(auto c:adj[v]){
        if(c==p)continue;
        int aux = dfs_sz(c,v,he+1);
        st[v]+=aux;
        if(aux>heavy_sz){
            heavy_sz=aux;
            heavy_c=c;
        }
    }
    heavy[v]=heavy_c;
    tout[v]=temp++;
    return st[v];
}
 
 
void dfs_hld(int v=1,int p=1,int hd=1){
    // dbg("v_h",v)
    id[v]=cur++;
    update(id[v],val[v]);
    head[v]=hd;
    if(heavy[v]!=-1){
        dfs_hld(heavy[v],v,hd);
    }
 
    for(auto c:adj[v]){
        if(c==p || c==heavy[v])continue;
        dfs_hld(c,v,c);
    }
}
 
void process(){
    dfs_sz();
    dfs_hld();
}
 
 
int query(int a,int b){
    int res=0;
    // heads diferentes
    for(;head[a]!=head[b];b=up[head[b]][0]){
        if(h[head[a]]>h[head[b]])swap(a,b);
        int aux = get(id[head[b]],id[b]);
        res=max(aux,res);
    }
    //heads iguais
    if(h[a]>h[b])swap(a,b);
    int aux=get(id[a],id[b]);
    res=max(res,aux);
    return res;
}
 
bool isAncestor(int a,int b){
    return tin[a]<=tin[b] && tout[a]>=tout[b];
}
 
int lca(int a,int b){
    if(isAncestor(a,b))return a;
    if(isAncestor(b,a))return b;
    rep(j,0,19){
        int i = 18-j;
        if(!isAncestor(up[a][i],b))a=up[a][i];
    }
    return up[a][0];
}
```