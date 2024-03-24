/**
 * Author: Wallace
 * Date: 24/03/2024
 * Description: A set that contains closed [l, r] interval which are disjoint (no intersection).
 * This set is ordered and each interval [l1, r1] < [l2, r2] has r1 < l2.
 * When a new interval is added, it checks which intersections will occur and rearranges the intervals.
 * Time: O(log(N)) per insertion, slow constant
 * Status: Tested (https://codeforces.com/group/DFlg3zUlDY/contest/446247/problem/C)
 */

// keeps track of disjoint closed intervals [l, r]
// a new interval added may replace parts of an older one
struct IntervalSet {
    using T = array<ll, 3>;
    set<T> ranges;

    void add(T arr) {
        auto [l, r, k] = arr;

        while(ranges.upper_bound({r, INF, INF}) != ranges.begin()) {
            auto itr = prev(ranges.upper_bound({r, INF, INF}));
            auto [l2, r2, k2] = *itr;
            
            if (r2 < l) break;
            // garantees that there is an intersection: l2 <= r and r2 >= l

            ranges.erase(itr);

            if (l2 <= l-1) {
                ranges.insert({l2, l-1, k2});
            }

            if (r+1 <= r2) {
                ranges.insert({r+1, r2, k2});
            }
        }
        ranges.insert({l, r, k});
    }
};