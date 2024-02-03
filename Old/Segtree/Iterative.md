#### Concepts

- Uses *2n* memory.
- Notation is *node_index*: each segment is **[left border included, right excluded)**
- Leaves are stored in continuous nodes with indices **[n, 2n)**.
- *build()* is done bottom up, from bigger indices (leaves) to index 1 (highest node)
- updating parent nodes is done bottom up.

- TLDR: **witchcraft**
  
## Iterative P-sum Classic Segtree with MOD

```cpp
struct Segtree{
    vector<ll> t;
    int n;
 
    Segtree(int n){
        this->n = n;
        t.assign(2*n, 0);
    }
 
    ll merge(ll a, ll b){
        return (a + b) % MOD;
    }
 
    void build(){
        for(int i=n-1; i>0; i--)
            t[i]=merge(t[i<<1], t[i<<1|1]);
    }
 
    ll query(int l, int r){ // [l, r]
        ll resl=0, resr=0;
        for(l+=n, r+=n+1; l<r; l>>=1, r>>=1){
            if(l&1) resl = merge(resl, t[l++]);
            if(r&1) resr = merge(t[--r], resr);
        }
        return merge(resl, resr);
    }
 
    void update(int p, ll value){
        p+=n;
        for(t[p]=(t[p] + value)%MOD; p >>= 1;)
            t[p] = merge(t[p<<1], t[p<<1|1]);
    }
 
};
```

## Iterative Range-Increment Range-Maximum (Lazy)

!! needs testing !!

```cpp
int h = sizeof(int) * 8 - __builtin_clz(n);
int d[N];

const int N = 1e5;  // limit for array size
int n;  // array size
int t[2 * N];


void apply(int p, int value) {
  t[p] += value;
  if (p < n) d[p] += value;
}

void build(int p) {
  while (p > 1) p >>= 1, t[p] = max(t[p<<1], t[p<<1|1]) + d[p];
}

void push(int p) {
  for (int s = h; s > 0; --s) {
    int i = p >> s;
    if (d[i] != 0) {
      apply(i<<1, d[i]);
      apply(i<<1|1, d[i]);
      d[i] = 0;
    }
  }
}

void inc(int l, int r, int value) {
  l += n, r += n;
  int l0 = l, r0 = r;
  for (; l < r; l >>= 1, r >>= 1) {
    if (l&1) apply(l++, value);
    if (r&1) apply(--r, value);
  }
  build(l0);
  build(r0 - 1);
}

int query(int l, int r) {
  l += n, r += n;
  push(l);
  push(r - 1);
  int res = -2e9;
  for (; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = max(res, t[l++]);
    if (r&1) res = max(t[--r], res);
  }
  return res;
}
```