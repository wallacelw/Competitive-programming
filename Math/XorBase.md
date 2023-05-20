## Xor Base

```cpp
struct XorBase {
    vector<ll> base;

    ll reduce(ll vec) {
        for(auto b : base) vec = min(vec, vec^b);
        return vec; 
    }

    void add(ll vec) {
        base.pb(vec);
    }
};
```