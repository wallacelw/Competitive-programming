/**
 * Author: Wallace
 * Date: 10/08/2024
 * Description: Basic Inverted Segment tree for
 * point query stored value, range increase
 * When initializing, choose an appropriate value for n=R.
 * Time: O(N \log(N)) to build, O(\log{N}) to range increase or point query
 * Status: Tested (https://atcoder.jp/contests/abc340/submissions/56587017)
 */

// [0, n] segtree for point query stored value, range increase
struct Segtree {
    struct Node {
        // correctly initialize default null values:
        ll sum = 0;
    };

    ll L=0, R;
    vector<ll> v;
    vector<Node> t;

    Segtree(ll n) : R(n), v(n+1), t(4*(n+1)) {}

    Node merge(Node a, Node b) {
        return Node {
            // merge operation:
            a.sum + b.sum
        };
    }

    void build(ll l, ll r, ll i) {
        if (l == r) {
            t[i] = Node {
                // leaf element:
                v[l]
            };
            return;
        }
        ll mid = (l+r)/2;
        build(l, mid, 2*i);
        build(mid+1, r, 2*i+1);
        t[i] = Node{};
    }
    void build() {
        build(L, R, 1);
    }
    
    // [a, b] are the range limits for the query
    // [l, r] are the internal variables of the t
    void increase(ll inc, ll a, ll b, ll l, ll r, ll i) {
        if (b < l or r < a) return;
        else if (a <= l and r <= b) {
            // increase operation
            t[i].sum += inc;
            return;
        }
        ll mid = (l+r)/2;
        increase(inc, a, b, l, mid, 2*i);
        increase(inc, a, b, mid+1, r, 2*i+1);
    }
    void increase(ll inc, ll a, ll b) {
        increase(inc, a, b, L, R, 1);
    }
 
    Node query(ll pos, ll l, ll r, ll i) {
        if (l == r) return t[i];
        ll mid = (l+r)/2;
        if (pos <= mid) 
            return merge(t[i], query(pos, l, mid, 2*i));
        else 
            return merge(t[i], query(pos, mid+1, r, 2*i+1));
    }
    Node query(ll pos) {
        return query(pos, L, R, 1);
    }
};
