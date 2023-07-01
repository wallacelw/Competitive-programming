## Hashing

May have complications with time limit, should avoid hashing

```cpp
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// hash(s) -> s[0]*P^n + s[1]*P^(n-1) + ... + s[n-1]*P + s[n]
struct Hashing {
    vector<ll> mods = { // multiple mods to surpass colision
        1000000009,1000000021,1000000033,
        1000000087,1000000093,1000000097,
        1000000103,1000000123,1000000181,
        1000000207,1000000223,1000000241,
        1000000271,1000000289,1000000297
    };

    ll num; // number of mods used (3 is a good number)
    ll P = 131; // more than ascii
    vector<unordered_set<ll>> cnt;
    vector<vector<ll>> h, p;

    Hashing(string &s, ll n = 3) : num(n) { // O(len(s) * num)
        shuffle(mods.begin(), mods.end(), rng);
        ll len = (ll) s.size();
        cnt.assign(n, unordered_set<ll>());
        h.assign(n, vector<ll>(len));
        p.assign(n, vector<ll>(len));

        for(ll i=0; i<num; i++) {
            p[i][0] = 1, h[i][0] = s[0];
            for(ll j=1; j<len; j++) {
                p[i][j] = (p[i][j-1] * P) % mods[i];
                h[i][j] = (h[i][j-1] * P + s[j]) % mods[i]; 
            }
        }
    }   

    // hash of s[l...r]
    vector<ll> get(ll l, ll r) {  // O(num)
        vector<ll> vec(num);
        for(ll i=0; i<num; i++) {
            vec[i] = h[i][r];
            if (l > 0)
                vec[i] = vec[i] - (h[i][l-1] * p[i][r-l+1]) % mods[i];
            if (vec[i] < 0)
                vec[i] += mods[i];
        }
        return vec;
    }
    
    // hash of t
    vector<ll> get(string &t) { // O(len(t) * num)
        ll len = (ll) t.size();
        vector<ll> vec(num);
        for(ll i=0; i<num; i++) {
            ll pow = 1, hash = t[0];
            for(ll j=1; j<len; j++) {
                pow = (pow * P) % mods[i];
                hash = (hash * P  + t[j]) % mods[i]; 
            }
            vec[i] = hash;
        }
        return vec;
    }

    void add(vector<ll> &vec) { // O(num)
        for(ll i=0; i<num; i++)
            cnt[i].insert(vec[i]);
    }

    bool check(vector<ll> &vec) { // O(num)
        for(ll i=0; i<num; i++)
            if (!cnt[i].count(vec[i])) return 0;
        return 1;
    }
};
```