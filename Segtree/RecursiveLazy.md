## Recursive Segtree with Lazy propagation

Needs refactoring :-( to leave only 1 version

### Most recent version (Max range query, increase range update)

```cpp
ll L = 1, R; // construct Seg with R value and build() afterwards
struct SegtreeLazy{

    struct Node {
        ll mx = -LLINF;
    };

    Node merge(Node a, Node b) {
        return Node{
            max(a.mx, b.mx)
        };
    }

    vector<ll> v, lazy;
    vector<Node> tree;

    SegtreeLazy(ll n) {
        R = n;
        tree.assign(4*(R-L+2), Node{});
        lazy.assign(4*(R-L+2), 0);
        v.assign((R-L+2), 0);
    }

    void build(ll l=L, ll r=R, ll i=1) {
        if (l == r) {
            tree[i] = Node{
                v[l]
            };
        }
        else{
            ll mid = (l+r)/2;
            build(l, mid, 2*i);
            build(mid+1, r, 2*i+1);
            tree[i] = merge(tree[2*i], tree[2*i+1]);
        }
        lazy[i] = 0;
    }

    void propagate(ll l, ll r, ll i){
        if(lazy[i]) {
            tree[i].mx += lazy[i];

            if(l != r){
                lazy[2*i] = lazy[2*i] + lazy[i];
                lazy[2*i+1] = lazy[2*i+1] + lazy[i];
            }
            
            lazy[i] = 0;
        }
    }

    // [left, right] = (selected interval for the query)
    // l, r = the variables used for the nodes boundaries

    // increase function adds 'val' to [left, right]
    void increase(ll left, ll right, ll val, ll l=L, ll r=R, ll i=1){
        propagate(l, r, i);

        if (right < l or r < left) return;

        else if (left <= l and r <= right){
            lazy[i] = lazy[i] + val;
            propagate(l, r, i);
        }

        else{
            ll mid = (l+r)/2;
            increase(left, right, val, l, mid, 2*i);
            increase(left, right, val, mid+1, r, 2*i+1);
            tree[i] = merge(tree[2*i], tree[2*i+1]);
        }
    }

    Node query(ll left, ll right, ll l=L, ll r=R, ll i=1){
        propagate(l, r, i);

        if (right < l or r < left) return Node{};

        else if (left <= l and r <= right) return tree[i];

        else{
            ll mid = (l+r)/2;
            return merge(
                query(left, right, l, mid, 2*i),
                query(left, right, mid+1, r, 2*i+1)
            );
        }
    }
};
```

### Sum range query, increase range update

```cpp
ll L = 1, R;
struct SegtreeLazy{
    vector<ll> tree, lazy, v;

    SegtreeLazy() {
        tree.assign(4*(R-L+2), 0);
        lazy.assign(4*(R-L+2), 0);
        v.assign((R-L+2), 0);
    }

    void build(ll l=L, ll r=R, ll i=1) {
        if (l == r) tree[i] = v[l];
        else{
            ll mid = (l+r)/2;
            build(l, mid, 2*i);
            build(mid+1, r, 2*i+1);
            tree[i] = tree[2*i] + tree[2*i+1];
        }
        lazy[i] = 0;
    }

    void propagate(ll l, ll r, ll i){
        if(lazy[i]) {
            tree[i] += lazy[i] * (r-l+1);
            if(l != r){
                lazy[2*i] += lazy[i];
                lazy[2*i+1] += lazy[i];
            }
            else v[l] += lazy[i]; // update array
            lazy[i] = 0;
        }
    }

    // [left, right] = (selected interval for the query)
    // l, r = the variables used for the vertex limits

    // increase function adds 'val' to [left, right]
    void increase(ll left=L, ll right=R, ll val=0, ll l=L, ll r=R, ll i=1){
        propagate(l, r, i);

        if (right < l or r < left) return;

        else if (left <= l and r <= right){
            lazy[i] += val;
            propagate(l, r, i);
        }

        else{
            ll mid = (l+r)/2;
            increase(left, right, val, l, mid, 2*i);
            increase(left, right, val, mid+1, r, 2*i+1);
            tree[i] = tree[2*i] + tree[2*i+1];
        }
    }

    ll query(ll left=L, ll right=R, ll l=L, ll r=R, ll i=1){
        propagate(l, r, i);

        if (right < l or r < left) return 0;

        else if (left <= l and r <= right) return tree[i];

        else{
            ll mid = (l+r)/2;
            return (
                query(left, right, l, mid, 2*i) + 
                query(left, right, mid+1, r, 2*i+1)
            );
        }
    }
};
```

### Range Minimum Query, Update (Assignment) Query

```cpp
ll L = 1, R;
struct SegtreeLazy{
    vll tree, lazy, v;

    SegtreeLazy() {
        tree.assign(4*(R-L+2), 0);
        lazy.assign(4*(R-L+2), 0);
        v.assign((R-L+2), 0);
    }

    void build(ll l=L, ll r=R, ll i=1) {
        if (l == r) tree[i] = v[l];
        else{
            ll mid = (l+r)/2;
            build(l, mid, 2*i);
            build(mid+1, r, 2*i+1);
            tree[i] = min(tree[2*i], tree[2*i+1]);
        }
        lazy[i] = LLINF; // min query default value
    }

    void propagate(ll l, ll r, ll i){
        if(lazy[i] != LLINF) { // need to propagate lazy
            tree[i] = lazy[i];
            if(l != r)
                lazy[2*i] = lazy[2*i+1] = lazy[i];
            else 
                v[l] = lazy[i]; // update 'v' vector
            lazy[i] = LLINF;
        }
    }

    // [left, right] = (selected interval for the query)
    // l, r = the variables used for the vertex limits

    // update function changes all elements in [left, right] to val
    void update(ll left=L, ll right=R, ll val=0, ll l=L, ll r=R, ll i=1){
        propagate(l, r, i);

        if (right < l or r < left) return;

        else if (left <= l and r <= right){
            lazy[i] = val;
            propagate(l, r, i);
        }

        else{
            ll mid = (l+r)/2;
            update(left, right, val, l, mid, 2*i);
            update(left, right, val, mid+1, r, 2*i+1);
            tree[i] = min(tree[2*i], tree[2*i+1]);
        }
    }

    ll query(ll left=L, ll right=R, ll l=L, ll r=R, ll i=1){
        propagate(l, r, i);

        if (right < l or r < left) return LLINF;

        else if (left <= l and r <= right) return tree[i];

        else{
            ll mid = (l+r)/2;
            return min(
                query(left, right, l, mid, 2*i), 
                query(left, right, mid+1, r, 2*i+1)
            );
        }
    }
};
```

#### For MAX Query

Use the same code as min segtree, change:

**min()** -> **max()**
**LLINF** -> **-LLINF**

### Complex Lazy Problems

**Requirements:** to be able to *propagate/push* the lazy stored updates. In other words, the property of **Aggregation:** to transfer the data saved in *lazy[i]* to *tree[i]* and also the property of **Composition:** to push the updates to the children (*lazy[i]* to *lazy[2*i]* and *lazy[i]* to *lazy[2*i+1]*).

#### Example1:

*range increase query by x*
*range sum of the squares* = a[l]^2 + ... + a[r]^2

```cpp
// import this struct
struct intM{};

ll L = 1, R; // Declare R = n and also use build() afterwards -_- macake
struct SegtreeLazy{

    struct Node {
        intM val;
        intM sqr;
    };

    Node merge(Node a, Node b) {
        return Node{
            a.val + b.val,
            a.sqr + b.sqr
        };
    }

    vector<intM> v, lazy;
    vector<Node> tree;

    SegtreeLazy() {
        tree.assign(4*(R-L+2), Node{});
        lazy.assign(4*(R-L+2), intM{});
        v.assign((R-L+2), intM{});
    }

    void build(ll l=L, ll r=R, ll i=1) {
        if (l == r) {
            tree[i] = Node{
                v[l],
                v[l] * v[l]
            };
        }
        else{
            ll mid = (l+r)/2;
            build(l, mid, 2*i);
            build(mid+1, r, 2*i+1);
            tree[i] = merge(tree[2*i], tree[2*i+1]);
        }
        lazy[i] = intM{};
    }

    void propagate(ll l, ll r, ll i){
        if(lazy[i].val) {
            tree[i].sqr = tree[i].sqr + (intM(2) * lazy[i] * tree[i].val);
            tree[i].sqr = tree[i].sqr + (lazy[i] * lazy[i] * intM(r-l+1));

            tree[i].val = tree[i].val + (lazy[i] * intM(r-l+1));

            if(l != r){
                lazy[2*i] = lazy[2*i] + lazy[i];
                lazy[2*i+1] = lazy[2*i+1] + lazy[i];
            }
            
            lazy[i] = intM{};
        }
    }

    // [left, right] = (selected interval for the query)
    // l, r = the variables used for the vertex limits

    // increase function adds 'val' to [left, right]
    void increase(ll left=L, ll right=R, ll val=0, ll l=L, ll r=R, ll i=1){
        propagate(l, r, i);

        if (right < l or r < left) return;

        else if (left <= l and r <= right){
            lazy[i] = lazy[i] + intM(val);
            propagate(l, r, i);
        }

        else{
            ll mid = (l+r)/2;
            increase(left, right, val, l, mid, 2*i);
            increase(left, right, val, mid+1, r, 2*i+1);
            tree[i] = merge(tree[2*i], tree[2*i+1]);
        }
    }

    Node query(ll left=L, ll right=R, ll l=L, ll r=R, ll i=1){
        propagate(l, r, i);

        if (right < l or r < left) return Node{};

        else if (left <= l and r <= right) return tree[i];

        else{
            ll mid = (l+r)/2;
            return merge(
                query(left, right, l, mid, 2*i),
                query(left, right, mid+1, r, 2*i+1)
            );
        }
    }
};

int32_t main(){ sws;
    ll n, q; cin >> n >> q;
    R = n;

    SegtreeLazy st;

    for(ll i=1; i<=n; i++) {
        ll x; cin >> x;
        st.v[i] = intM(x);
    }

    st.build();

    while(q--) {
        char c; cin >> c;
        if (c == 'u') {
            ll l, r, x; cin >> l >> r >> x;
            st.increase(l, r, x);
        }
        else {
            ll l, r; cin >> l >> r;
            cout << st.query(l, r).sqr.val << endl;
        }
    }
}   
```

## Range increase and set queries

```cpp
int t[MAXN<<2];
pii lazy[MAXN<<2];
 
pii combineLz(pii a,pii b){
    if(b.ff==0)return a;
    if(a.ff==2)return a;
    if(b.ff==1 && a.ff==1)return mp(1,a.ss+b.ss);     
    return mp(2,a.ss+b.ss);
}
 
void push(int v,int tl,int tr){
    if(lazy[v].ff==0LL)return;
    lazy[v<<1]=combineLz(lazy[v],lazy[v<<1]);
    lazy[v<<1|1]=combineLz(lazy[v],lazy[v<<1|1]);
    int tm = (tl+tr)/2;
 
    if(lazy[v].ff==1){
        t[v<<1]+=((tm-tl+1)*lazy[v].ss);
        t[v<<1|1]+=((tr-tm)*lazy[v].ss);
    }else{
        t[v<<1]=(tm-tl+1)*lazy[v].ss;
        t[v<<1|1]=((tr-tm)*lazy[v].ss);
    }
 
    lazy[v]=mp(0,0);
 
}
void build(int a[],int v,int tl,int tr){
    if(tl==tr){
        t[v]=a[tl];
        return;
    }
    int tm = (tl+tr)/2;
    build(a,v<<1,tl,tm);
    build(a,v<<1|1,tm+1,tr);
    t[v]=t[v<<1]+t[v<<1|1];
    
}
 
void update(int v,int tl,int tr,int l,int r,int op,int val){
    if(tr<l || tl>r)return;
 
    if(tl==l && tr==r){
        int aux =((tr-tl+1)*val);
       if(op==1){
            t[v]+= aux;
       }else{
            t[v]=aux;
       }
       lazy[v]=combineLz(mp(op,val),lazy[v]);
       return;
    }
 
    push(v,tl,tr);
    int tm = (tl+tr)/2;
    update(v<<1,tl,tm,l,min(tm,r),op,val);
    update(v<<1|1,tm+1,tr,max(l,tm+1),r,op,val);
    t[v]=t[v<<1]+t[v<<1|1];
   
}
 
int get(int v,int tl,int tr,int l,int r){
 
    if(tr<l || tl>r){
        return 0 ;
    }
 
    if(tl==l && tr==r){
        return t[v];
    }
 
    push(v,tl,tr);
    int tm = (tl+tr)/2;
    return get (v<<1,tl,tm,l,min(tm,r))+get(v<<1|1,tm+1,tr,max(l,tm+1),r);
}
```