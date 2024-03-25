/**
 * Author: Wallace
 * Date: 25/03/2024
 * Description: Efficiently compute a bitmask dp, in which a subset of this bitmask
 * contributes for the value of this bitmask.
 * Time: O(2^N N), N = number of bits
 * Status: Tested (https://cses.fi/problemset/result/8829466/)
 */

// problem: Given a list of n integers, your task is to calculate for each element x:
// the number of elements y such that x | y = x
// the number of elements y such that x & y = x
// the number of elements y such that x & y != 0

const ll LOGMAX = 20;
ll dp[1 << LOGMAX];
ll dp2[1 << LOGMAX];

int32_t main(){ sws;
    ll n; cin >> n;
    
    vector<ll> a(n);
    for(auto &val : a) cin >> val;

    ll full = (1LL << LOGMAX) - 1;

    for(auto val : a) dp2[full^val] += 1;
    for(auto val : a) dp[val] += 1;

    for(ll b=0; b<LOGMAX; b++) {
        for(ll mask=0; mask<(1LL<<LOGMAX); mask++) {
            if (mask & (1LL << b)) {
                dp[mask] += dp[mask ^ (1LL << b)];
                dp2[mask] += dp2[mask ^ (1LL << b)];
            }
        }
    }

    for(auto val : a) {
        cout << dp[val] << " ";
        cout << dp2[full ^ val] << " ";
        cout << n - dp[full^val] << endl;
    }
}  