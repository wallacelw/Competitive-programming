/**
 * Author: Wallace, USACO
 * Date: 22/04/2024
 * Description: Computes the LIS size and also the auxiliar vector used to compute it.
 * the LIS is STRICTLY INCREASING, but the given array can have duplicated values, the algorithm still works!
 * Time: O(n log{n})
 * Status: Tested (https://cses.fi/problemset/result/9087101/)
*/


// returns {lis_size, vector<ll> mn[i] -> minimum last value of a LIS of size i}
pair<ll, vector<ll>> lis(vector<ll> x) { 
    ll n = x.size();
    vector<ll> mn(n+1, INF); // mn[i] -> min value to achieve a LIS with size i
    mn[0] = -INF;
    for(auto val : x) {
        // find first element greater or equal than val
        ll pos = lower_bound(mn.begin(), mn.end(), val) - mn.begin();
        mn[pos] = val;
    }
    ll sz = lower_bound(mn.begin(), mn.end(), INF) - mn.begin() - 1;
    return {sz, mn};
}

// alternative code from USACO (not tested, but should work and vector index is off by an offset of -1)
int find_lis(vector<int> a) {
	vector<int> dp;
	for (int i : a) {
		int pos = lower_bound(dp.begin(), dp.end(), i) - dp.begin();
		if (pos == dp.size()) {
			// we can have a new, longer increasing subsequence!
			dp.push_back(i);
		} else {
			// oh ok, at least we can make the ending element smaller
			dp[pos] = i;
		}
	}
	return dp.size();
}
