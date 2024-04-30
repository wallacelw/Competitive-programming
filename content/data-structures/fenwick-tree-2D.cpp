/**
 * Author: Wallace
 * Date: 30/04/2024
 * Description: Simple 2D Fenwick Tree with point increase, 2D range sum query. 1-idx
 * Time: O(log{n} \cdot log{m}) to add, get psum, or range sum query
 * Status: Tested (https://cses.fi/problemset/result/9148069/)
*/

// 1-idx, cover the grid of rows [1, n] and columns [1, m]
struct FT2D {
    ll n, m;
    vector<vll> bit;

    FT2D(ll nn, ll mm) : n(nn), m(mm) {
        bit.assign(n+1, vll(m+1, 0));
    }

    void add(ll x, ll y, ll delta) { // O(log(n)*log(m))
        for(ll i=x; i<=n; i += i & -i)
            for(ll j=y; j<=m; j += j & -j)
                bit[i][j] += delta;
    }

    ll sum(ll x, ll y) { // O(log(n)*log(m))
        ll ans = 0;
        for(ll i=x; i>=1; i -= i & -i)
            for(ll j=y; j>=1; j -= j & -j)
                ans += bit[i][j];
        return ans;
    }

    ll query(ll x1, ll y1, ll x2, ll y2) { // O(log(n)*log(m))
        x1--; y1--; // to make point {x1, y1} inclusive
        return sum(x2, y2) - sum(x2, y1) - sum(x1, y2) + sum(x1, y1);
    }
};