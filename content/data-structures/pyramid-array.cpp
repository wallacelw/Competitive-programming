/**
 * Author: Wallace
 * Date: 12/04/2024
 * Description: algorithm to find the min-cost of sorting an array in a pyramid order
 * Time: O(N \log(N)), or O(N \log^2(N)) if iterating the map directly
 * Status: Tested in cses, https://codeforces.com/gym/102082(G)
 */

int32_t main() { sws;
    ll n; cin >> n;
    map<ll, vll> freq;
    for(ll i=0; i<n; i++) {
        ll val; cin >> val;
        freq[val].pb(i);
    }
    ordered_set<ll> os; // os with indexes of greater processed elements
    ll ans = 0;
    // iterate from greater values to lesser one.
    // for each element, 
    // consider inserting it to the left of all greater elements
    // or to the right of all greater elements
    for(auto itr = freq.rbegin(); itr != freq.rend(); itr++) {
        auto [val, vec] = *itr;
        for(auto idx : vec) {
            ll pos = os.order_of_key({idx});
            ll left_cost = pos;
            ll right_cost = (ll)os.size() - pos;
            ans += min(left_cost, right_cost);
        }
        for(auto idx : vec) os.insert(idx);
    }
    cout << ans << endl;
}