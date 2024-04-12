/**
 * Author: Cp-Algo, Wallace
 * Date: 12/04/2024
 * Description: Optimize $O(n^3)$ to $O(n^2)$ dp with transitions of finding a optimal division point k for [l, r].
 * Time: O(n^2)
 * Status: Tested (https://cses.fi/problemset/result/8995793/)
*/

// dp[l][r] (inclusive) -> min cost
// opt[l][r] (inclusive) -> optimal spliting point k in l<=k<=r
ll dp[MAX][MAX], opt[MAX][MAX];
 
ll knuth(vector<ll> &vec) {
    // vec indexed with 1-idx, vec[0] = 0
    ll n = vec.size() - 1; 
 
    vector<ll> ps(n+1, 0);
    for(ll i=1; i<=n; i++) {
        ps[i] = ps[i-1] + vec[i];
    }
    auto C = [&](ll l, ll r) {
        return ps[r] - ps[l-1];
    };
 
    for(ll i=1; i<=n; i++) {
        opt[i][i] = i;
    }
 
    for(ll l=n-1; l>=1; l--) {
        for(ll r=l+1; r<=n; r++) {
            ll mn = INF;
            ll cost = C(l, r);
            for(ll k=opt[l][r-1]; k<=min(r-1, opt[l+1][r]); k++) {
                ll aux = dp[l][k] + dp[k+1][r] + cost;
                if (aux <= mn) {
                    mn = aux;
                    opt[l][r] = k;
                }
            }
            dp[l][r] = mn;
        }
    }
 
    return dp[1][n];
}
