/**
 * Author: Wallace
 * Date: 30/04/2024
 * Description: Simple 1D Fenwick Tree with point increase, range sum query. 1-idx
 * Time: O(log{n}) to add, get psum, or range sum query
 * Status: Tested (https://cses.fi/problemset/result/9148044/)
*/

// 1-idx, vector covers [1, n]
struct FT {
    ll n;
    vector<ll> bit;
    
    FT(ll sz) : n(sz), bit(sz+1, 0) { }

    // add delta to positon pos
    void add(ll pos, ll delta) { // O(log(n))
        for (; pos <= n; pos += pos & -pos)
            bit[pos] += delta;
    }

    // get prefix sum of [1, pos]
    ll sum(ll pos) { // O(log(n))
        ll ans = 0;
        for (; pos >= 1; pos -= pos & -pos)
            ans += bit[pos];
        return ans;
    }

    // query the sum of range [l, r]
    ll query(ll l, ll r) { // O(log(n))
        return sum(r) - sum(l - 1);
    }
};
