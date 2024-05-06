/**
 * Author: CP-algo, Wallace
 * Date: 12/04/2024
 * Description: Optimize an $O(m n^2)$ dp to $O(m n log(n))$ using divide and conquer. 
 * cost function must have quadrangle inequality ("wider is worse")
 * Time: O(m n \log{n}) 
 * Status: Tested (https://cses.fi/problemset/result/8998923/)
*/

// m partitions, n elements
ll divideConquerDP(ll m, vector<ll> &vec) {
    // vec indexed with 1-idx, vec[0] = 0
    ll n = vec.size() - 1;
    
    vector<ll> ps(n+1, 0);
    for(ll i=1; i<=n; i++) {
        ps[i] = ps[i-1] + vec[i];
    }
    auto cost = [&](ll l, ll r) {
        ll sum = ps[r] - ps[l-1];
        return sum * sum;
    };

    vector<ll> cur(n+1, 0), nxt(n+1);

    // O(n log(n))
    function<void(ll, ll, ll, ll)> compute = [&](ll l, ll r, ll optl, ll optr) {
        if (r < l) return;

        ll mid = (l+r)/2;

        ll best = INF;
        ll opt = -1;
        for(ll k=optl; k<=min(mid, optr); k++) {
            ll val = cur[k-1] + cost(k, mid);
            if (val < best) {
                best = val;
                opt = k;
            }
        }
        nxt[mid] = best;

        compute(l, mid-1, optl, opt);
        compute(mid+1, r, opt, optr);
    };

    for(ll i=1; i<=n; i++) // 1 partition
        cur[i] = cost(1, i);

    for(ll i=1; i<m; i++) { // m partitions
        nxt[0] = 0; 
        compute(1, n, 1, n);
        swap(cur, nxt);
    }

    return cur[n];
}