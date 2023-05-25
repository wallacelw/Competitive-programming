## Xor Basis

```cpp
struct XorBasis {
    vector<ll> B;
    
    ll reduce(ll a) {
        for(auto b : B) a = min(a, a^b);
        return a;
    }

    void add(ll a) {
        ll val = reduce(a);
        if (val) B.pb(val);
    }
};
```

**Extended:**

```cpp
struct XorBasis {
    vector<ll> basis;
    ll dim = 0, mx = 0;

    ll reduce(ll vec) {
        for(auto b : basis) vec = min(vec, vec^b);
        return vec;
    }

    void add(ll vec) {
        ll val = reduce(vec);
        if (val) {
            basis.pb(val);
            mx = max(mx, mx^val);
            dim += 1;
        }
    }

    void jordan() {
        sort(basis.begin(), basis.end(), greater<ll>());
        for(ll i=1; i<(ll)basis.size(); i++) {
            for(ll j=0; j<i; j++) {
                basis[j] = min(basis[j], basis[j]^basis[i]);
            }
        }
    }
};
```