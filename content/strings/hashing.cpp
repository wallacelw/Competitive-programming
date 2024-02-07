/**
 * Author: Wallace
 * Date: 07/02/2024
 * Description: Create a numerical value for a string by using 
 * polynomial hashing
 * Time: O(n) to build, O(1) per query
 * Status: Tested (https://cses.fi/problemset/result/8411973/)
 */

// s[0]*P^n + s[1]*P^(n-1) + ... + s[n]*P^0
// 0-idx
struct Hashing {
    ll n, mod;
    string s;
    vector<ll> p, h; // p = P^i, h = accumulated hash sum

    const ll P = 31; // can be 53

    Hashing(string &s_, ll m)
      : n(s_.size()), s(s_), mod(m), p(n), h(n) {
            
        for(ll i=0; i<n; i++)
            p[i] = (i ? P*p[i-1] : 1) % mod;

        for(ll i=0; i<n; i++)
            h[i] = (s[i] + P*(i ? h[i-1] : 0)) % mod;
    }

    ll query(ll l, ll r) { // [l, r] inclusive (0-idx)
        ll hash = h[r] - (l ? (p[r-l+1]*h[l-1]) % mod : 0);
        return hash < 0 ? hash + mod : hash;
    }
};

// for codeforces:
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int32_t main() { sws;
    vector<ll> mods = {
        1000000009,1000000021,1000000033,
        1000000087,1000000093,1000000097,
        1000000103,1000000123,1000000181,
        1000000207,1000000223,1000000241,
        1000000271,1000000289,1000000297
    };

    shuffle(mods.begin(), mods.end(), rng);
    
    string s; cin >> s;

    Hashing hash(s, mods[0]);
}