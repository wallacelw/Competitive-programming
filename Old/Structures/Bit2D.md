## 2-Dimensional Binary Indexed Tree

```cpp
// 1-Indexed
struct FT2D {
    ll n, m;
    vector<vll> bit;

    FT2D(ll nn, ll mm) : n(nn), m(mm) {
        bit.assign(nn+1, vll(mm+1, 0));
    }

    void add(ll x, ll y, ll delta) {
        for(ll i=x; i<=n; i += i & -i)
            for(ll j=y; j<=m; j += j & -j)
                bit[i][j] += delta;
    }

    ll sum(ll x, ll y) {
        ll ans = 0;
        for(ll i=x; i>=1; i -= i & -i)
            for(ll j=y; j>=1; j -= j & -j)
                ans += bit[i][j];
        return ans;
    }

    ll query(ll x1, ll y1, ll x2, ll y2) {
        x1--; y1--; // if (x1, y1) are originally inclusive
        return sum(x2, y2) - sum(x2, y1) - sum(x1, y2) + sum(x1, y1);
    }
};
```