/**
 * Author: Quirino, Wallace
 * Date: 21/01/2025
 * Description: permutation functions to apply and do the exponentiation
 * Status: tested in SBC summer 2025
*/

// p[i] = j => "pos j will be put in pos i"
vector<ll> apply_permutation(vector<ll> const &p, vector<ll> const &cur) {
    ll n = p.size();
    vector<ll> ans(n);
    for(ll i=0; i<n; i++) {
        ans[i] = cur[p[i]];
    }
    return ans;
}

// p[i] = j => "pos j will be put in pos i"
vector<ll> fexp_permutation(vector<ll> const& p, ll e) {
    if (e == 0) {
        ll n = p.size();
        vector<ll> ans(n);
        iota(ans.begin(), ans.end(), 0);
        return ans;
    }
    auto t = fexp_permutation(p, e/2);
    t = apply_permutation(t, t);
    if (e & 1) t = apply_permutation(t, p);
    return t;
}