/**
 * Author: Wallace
 * Date: 03/08/2024
 * Description: Xor Basis
 * Time: O(size(base)) reduce(), add(); size(base) <= 64 for long long
 * Status: Tested!
*/

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


// Extended // 
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