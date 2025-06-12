/**
 * Author: Wallace
 * Date: 11/08/2024
 * Description: Xor Basis
 * Time: O(size(base)) = O(\log{mx\_val});
 * Status: Tested with lots of problems
*/

struct XorBasis {
    vector<ll> B; // basis
    
    ll reduce(ll vec) {
        for(auto b : B) vec = min(vec, vec^b);
        return vec;
    }

    void add(ll vec) {
        ll val = reduce(vec);
        if (val) B.pb(val);
    }
};

// Extended // 
struct XorBasis {
    vector<ll> B; // Basis
    
    ll dim() { return B.size(); } // O(1)

    ll reduce(ll vec) { // O(log(a_max))
        for(auto b : B) vec = min(vec, vec^b);
        return vec;
    }

    bool add(ll vec) { // O(log(a_max))
        ll val = reduce(vec);
        if (val) {
            B.pb(val);
            return true;
        }
        return false;
    }

    ll mxVal() { // O(log(a_max))
        ll mx = 0;
        for(auto b : B) mx = max(mx, mx^b);
        return mx;
    }

    void gaussJordan() { // O(log(a_max)^2)
        sort(B.begin(), B.end(), greater<ll>());
        for(ll i=1; i<(ll)B.size(); i++) {
            for(ll j=0; j<i; j++) {
                B[j] = min(B[j], B[j]^B[i]);
            }
        }
    }
};

// Problem description: (Ivan and Burgers)
// given a static array x[1, N]
// for each query, answer then max xor-sum of any subset in subarray [L, R]
// Contrains: 1 <= L <= R <= N, N <= 5e5, Q <= 5e5

// Probably the complexity is O(N log^2(N) + Q)
// Similarly, we can answer other type of queries related to xor-basis,
// because we will have it computed (Atcoder: H - Xor Query)
int32_t main(){ sws;
    ll n; cin >> n;

    vector<ll> x(n+1);
    for(ll i=1; i<=n; i++) {
        cin >> x[i];
    }

    vector<vector<pll>> queries(n+1);
    ll q; cin >> q;
    for(ll i=1; i<=q; i++) {
        ll l, r; cin >> l >> r;
        queries[r].pb({l, i});
    }
    
    vector<XorBasis> xb(n+1); // extended version of XorBasis
    vector<ll> ans(q+1);

    for(ll r=1; r<=n; r++) {

        // O(de bom), maybe log?
        for(ll l=r; l>=1; l--) {
            if (!xb[l].add(x[r])) break;
            // We can break here, because this xor-basis of L already contains a basis that doesn't need x[r]
            // Therefore, the xor-basis of L-1, L-2, ..., which contains the xor-basis of L, also doesn't need x[r]
        }

        // solve all queries ending in r,
        // knowing that all xor-basis are computed up to r.
        for(auto [left, i] : queries[r]) {
            ans[i] = xb[left].mx;
        }
    }

    for(ll i=1; i<=q; i++) {
        cout << ans[i] << endl;
    }
}