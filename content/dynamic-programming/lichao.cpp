/**
 * Author: Wallace, LeticiaFCS
 * Date: 06/05/2024
 * Description: Basic Li-chao tree implementation, in which every node
 * in a segment tree contains the one needed line that has the min/max query
 * Time: O(\log{N}) for add-line(), query(); O(\log^2{N}) for add-segment; N = max-value considered of X
 * Status: Tested (https://atcoder.jp/contests/dp/submissions/53206520, https://codeforces.com/gym/104555/my)
*/

// Lichao tree for minimum query
// to adapt to max query: 
// +INF -> -INF
// min() -> max()
// '>' -> '<' in add_line()
struct Lichao {
    struct Line {
        ll a = 0, b = +INF; // ax + b
        ll operator()(ll x) {
            return a*x + b;
        }
    };

    ll L = 0, R;
    vector<ll> v;
    vector<Line> tree;

    Lichao(ll n) : R(n), v(n+1), tree(4*(n+1)) {}

    void add_line(Line line, ll l, ll r, ll i) {
        ll mid = (l+r)/2;
        if (tree[i](mid) > line(mid)) {
            swap(tree[i], line);
        }
        if (tree[i](l) > line(l)) {
            add_line(line, l, mid, 2*i);
        }
        if (tree[i](r) > line(r)) {
            add_line(line, mid+1, r, 2*i+1);
        }
    }
    void add_line(Line line) {
        add_line(line, L, R, 1);
    }

    void add_segment(Line line, ll left, ll right, ll l, ll r, ll i) {
        if (left <= l and r <= right) {
            add_line(line, l, r, i);
            return;
        }
        ll mid = (l+r)/2;
        if (left <= mid) {
            add_segment(line, left, right, l, mid, 2*i);
        }
        if (mid < right) {
            add_segment(line, left, right, mid+1, r, 2*i+1);
        }
    }
    void add_segment(Line line, ll left, ll right) {
        add_segment(line, left, right, L, R, 1);
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