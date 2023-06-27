## Hashing

```cpp
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Hash {
    vector<unordered_set<ll>> h;
    vector<ll> mods = { // multiple mods to ignore colision
        1000000009,1000000021,1000000033,
        1000000087,1000000093,1000000097,
        1000000103,1000000123,1000000181,
        1000000207,1000000223,1000000241,
        1000000271,1000000289,1000000297
    };
    ll p = 31;
    ll num; // number of mods used

    Hash(ll n) : num(n) {
        h.assign(n, unordered_set<ll>());
        random_shuffle(mods.begin(), mods.end(), rng);
    }

    ll get(string const &s, ll p, ll m) { 
        ll val = 0, p_pow = 1;
        for(char c : s) {
            val = ( val + (c-'a'+1) * p_pow) % m;
            p_pow = (p_pow * p) % m;
        }
        return val;
    }

    void add(string const &s) {
        for(ll i=0; i<num; i++) {
            ll value = get(s, p, mods[i]);
            h[i].insert(value);
        }
    }

    bool query(string const& s) {
        for(ll i=0; i<num; i++) {
            ll val = get(s, p, mods[i]);
            if(!h[i].count(val)) return false;
        }
        return true; 
    }
};
```