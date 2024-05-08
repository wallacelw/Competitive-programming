/**
 * Author: CP-algo, Wallace
 * Date: 08/05/2024
 * Description: Optimize an $O(m n^2)$ dp to $O(m n log(n))$ using divide and conquer. 
 * cost function must have the quadrangle inequality ("wider is worse")
 * Time: O(m n \log(n)) 
 * Status: Tested (https://cses.fi/problemset/result/9206680/)
*/

int32_t main() { sws;
    // n elements, m partitions
    ll n, m; cin >> n >> m;
 
    vector<ll> vec(n+1);
    for(ll i=1; i<=n; i++) {
        cin >> vec[i];
    }
    
    vector<ll> ps(n+1, 0);
    for(ll i=1; i<=n; i++) {
        ps[i] = ps[i-1] + vec[i];
    }

    // cost the partition [l, r]
    auto cost = [&](ll l, ll r) {
        ll sum = ps[r] - ps[l-1];
        return sum * sum;
    };
    
    // dp[i][k] -> min cost; i = considered prefix, k = number of partitions
    // dp[i][k] = min{ dp[j-1][k-1] + cost([j, i]) }, j is the spliting point
    vector<vector<ll>> dp(n+1, vector<ll>(m+1, 0));
 
    // O(n log(n))
    function<void(ll, ll, ll, ll, ll)> solve = [&](ll k, ll l, ll r, ll optl, ll optr) {
        if (r < l) return;

        ll mid = (l+r)/2;
        dp[mid][k] = INF;
        ll opt = -1;

        for(ll j=optl; j<=min(mid, optr); j++) {
            ll val = dp[j-1][k-1] + cost(j, mid);
            if (val < dp[mid][k]) {
                dp[mid][k] = val;
                opt = j;
            }
        }
 
        solve(k, l, mid-1, optl, opt);
        solve(k, mid+1, r, opt, optr);
    };

    for(ll i=1; i<=n; i++) // one partition for all prefixes
        dp[i][1] = cost(1, i);
 
    for(ll k=2; k<=m; k++) { // computhe the other m partitions
        solve(k, 1, n, 1, n);
    }

    cout << dp[n][m] << endl;
}