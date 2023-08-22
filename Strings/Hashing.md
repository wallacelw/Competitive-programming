## Hashing

```cpp
vector<ll> mods = {
    1000000009,1000000021,1000000033,
    1000000087,1000000093,1000000097,
    1000000103,1000000123,1000000181,
    1000000207,1000000223,1000000241,
    1000000271,1000000289,1000000297
};
const ll P = 31; // can be 53

// s[0]*P^n + s[1]*P^(n-1) + ... + s[n]*P^0
struct Hashing {
    ll n, m; // n = s.size(), m = mods used
    string s;
    vector<vll> p, h;

    Hashing(string &ss, ll mm)
        : n(s.size()), s(ss), m(mm), p(m, vll(n)), h(m, vll(n)) {
        for(ll k=0; k<m; k++) {
            for(ll i=0; i<n; i++)
                p[k][i] = (i ? P*p[k][i-1] : 1) % mods[k];
            for(ll i=0; i<n; i++)
                h[k][i] = (s[i] + P*(i ? h[k][i-1] : 0)) % mods[k];
        }
    }

    ll query(ll l, ll r, ll k) { // [l, r] inclusive (0-idx), k = mod index
        ll hash = h[k][r] - (l ? (p[k][r-l+1]*h[k][l-1]) % mods[k] : 0);
        return hash < 0 ? hash + mods[k] : hash;
    }
};

int32_t main() { sws;
    shuffle(mods.begin(), mods.end(), rng);
}
```