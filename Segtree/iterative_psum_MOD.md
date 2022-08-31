# Iterative P-sum Classic Segtree with MOD

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