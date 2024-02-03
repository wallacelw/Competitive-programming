## MEX

```cpp
struct MEX {
    map<ll, ll> freq;
    set<ll> missing;

    MEX(ll max_val) { // O(n log(n))
        for(ll i=0; i<=max_val; i++)
            missing.insert(i);
    }

    ll get() { // O(1)
        if (missing.empty()) return 0;
        return *missing.begin();
    }

    void remove(ll val) { // O(log(n))
        freq[val]--;
        if (freq[val] == 0)
            missing.insert(val);
    }

    void add(ll val) { // O(log(n))
        freq[val]++;
        if (missing.count(val))
            missing.erase(val);
    }
};
```