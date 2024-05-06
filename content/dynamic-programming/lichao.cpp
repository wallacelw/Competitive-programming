/**
 * Author: Wallace, LeticiaFCS
 * Date: 06/05/2024
 * Description: Basic Li-chao tree implementation, in which every node
 * in a segment tree contains the one needed line that has the min/max query
 * Time: O(log{N}), N = size of the considered range for x \in [1, N]
 * Status: Tested (https://atcoder.jp/contests/dp/submissions/53205903)
*/

// Lichao tree for minimum query
// to adapt to max query: 
// +INF -> -INF
// min() -> max()
// '>' -> '<' in insert()
struct Lichao {
    struct Line {
        ll a = 0, b = +INF; // ax + b
        ll operator()(ll x) {
            return a*x + b;
        }
    };
 
    ll L = 1, R;
    vector<ll> v;
    vector<Line> tree;

    Lichao(ll n) : R(n), v(n+1), tree(4*(n+1)) {}
 
    void insert(Line line, ll l, ll r, ll i) {
        ll mid = (l+r)/2;

        if (tree[i](mid) > line(mid)) {
            swap(tree[i], line);
        }

        if (tree[i](l) > line(l)) {
            insert(line, l, mid, 2*i);
        }

        if (tree[i](r) > line(r)) {
            insert(line, mid+1, r, 2*i+1);
        }
    }
    void insert(Line line) {
        insert(line, L, R, 1);
    }
 
    ll query(ll x, ll l, ll r, ll i) {
        if (l == r) return tree[i](x);

        ll mid = (l+r)/2;
        ll ans = tree[i](x);

        if (x <= mid) {
            ans = min(ans, query(x, l, mid, 2*i));
        }
        else {
            ans = min(ans, query(x, mid+1, r, 2*i+1));
        }
        return ans;
    }
    ll query(ll x) {
        return query(x, L, R, 1);
    }
};