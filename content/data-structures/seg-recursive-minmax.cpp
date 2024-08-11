/**
 * Author: Wallace
 * Date: 20/03/2024 
 * Description: Basic Recursive Segment tree for
 * point update, range min/max query
 * When initializing, choose an appropriate value for (n = R) and call build()
 * Time: O(N \log(N)) to build, O(\log(N)) to update or query
 * Status: Tested {https://atcoder.jp/contests/abl/submissions/56586493}
 */

// [0, n] segtree for point assignment update, range min/max query
struct Segtree {
    struct Node {
        // correctly initialize default null values:
        ll mn = INF, mx = -INF;
    };

    ll L=0, R;
    vector<ll> v;
    vector<Node> t;
    
    Segtree(ll n) : R(n), v(n+1), t(4*(n+1)) {}
 
    Node merge(Node a, Node b) {
        return Node {
            // merge operation:
            min(a.mn, b.mn),
            max(a.mx, b.mx)
        };
    }

    void build(ll l, ll r, ll i) {
        if (l == r) {
            t[i] = Node {
                // leaf element:
                v[l],
                v[l]
            };
            return;
        }
        ll mid = (l+r)/2;
        build(l, mid, 2*i);
        build(mid+1, r, 2*i+1);
        t[i] = merge(t[2*i], t[2*i+1]);
    }
    void build() {
        build(L, R, 1);
    }

    void update(ll pos, ll val, ll l, ll r, ll i) {
        if (l == r) {
            // update(assignment) operation:
            t[i].mn = t[i].mx = val;
            return;
        }
        ll mid = (l+r)/2;
        if (pos <= mid)
            update(pos, val, l, mid, 2*i);
        else 
            update(pos, val, mid+1, r, 2*i+1);
        t[i] = merge(t[2*i], t[2*i+1]);
    }
    void update(ll pos, ll val) {
        update(pos, val, L, R, 1);
    }
    
    // [a, b] are the range limits for the query
    // [l, r] are the internal variables of the t
    Node query(ll a, ll b, ll l, ll r, ll i) {    
        if (b < l or r < a) return Node{}; // default null value
        else if (a <= l and r <= b) return t[i];
        ll mid = (l+r)/2;
        return merge(
            query(a, b, l, mid, 2*i), 
            query(a, b, mid+1, r, 2*i+1)
        );
    }
    Node query(ll a, ll b) {
        return query(a, b, L, R, 1);
    }
};