## Xor Basis

```cpp
struct XorBasis {
    vll basis;
    
    ll reduce(ll a) {
        for(auto b : basis) a = min(a, a^b);
        return a;
    }

    void add(ll a) {
        ll val = reduce(a);
        if (val) basis.pb(val);
    }
};
```