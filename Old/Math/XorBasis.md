## Xor Basis

```cpp
struct XorBasis {
    vector<ll> basis;
    
    ll reduce(ll vec) {
        for(auto b : basis) vec = min(vec, vec^b);
        return vec;
    }

    void add(ll vec) {
        ll val = reduce(vec);
        if (val) B.pb(val);
    }
};
```

**Extended:**

```cpp
struct XorBasis {
    vector<ll> basis;
    ll mx = 0;

    ll reduce(ll vec) {
        for(auto b : basis) vec = min(vec, vec^b);
        return vec;
    }

    void add(ll vec) {
        ll val = reduce(vec);
        if (val) {
            basis.pb(val);
            mx = max(mx, mx^val);
        }
    }

    ll dim() {
        return basis.size();
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

**Common problems:**

- Find if a vector can be formed by the basis ( if(reduce(val)) )
- Find how many linear combinations form a vector (ans = 2^(dim(kernel)))
- Find the maximum vector that can be formed (mx = max(mx, mx^b))