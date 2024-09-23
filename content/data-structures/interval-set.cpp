/**
 * Author: Wallace
 * Date: 23/09/2024
 * Description: A map that contains closed [l, r] interval which are disjoint (no intersection).
 * This set is ordered and each interval [l1, r1] < [l2, r2] has r1 < l2.
 * When a new interval is added, it checks which intersections will occur and rearranges the intervals.
 * Time: O(Q \log(N)) per insertion, slow constant
 * Status: Tested (https://codeforces.com/group/DFlg3zUlDY/contest/446247/problem/C, https://codeforces.com/gym/102059/problem/A)
 */

// keeps track of disjoint closed intervals [l, r]
// a new interval added may replace parts of an older one
struct IntervalSet {
    map<pair<ll, ll>, ll> interval;
    void add(ll a, ll b, ll val) {
        // remove intervals [l, r] with intersection with [a, b]
        while(interval.upper_bound({b, INF}) != interval.begin()) {
            auto itr = prev(interval.upper_bound({b, INF}));
            auto [l, r] = itr->first;
            auto k = itr->second;
            if (r < a) break;
            interval.erase(itr);
            if (l <= a-1) {
                interval[{l, a-1}] = k;
            }
            if (b+1 <= r) {
                interval[{b+1, r}] = k;
            }
        }
        interval[{a, b}] = val;
    }
};