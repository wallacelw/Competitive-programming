/**
 * Author: Wallace
 * Date: 20/03/2024 
 * Description: Basic Inverted Segment Tree for
 * point query stored value, range increase
 * When initializing, choose an appropriate value for n.
 * Time: O(N \log(N)) to build, O(\log{N}) to range increase or point query
 * Status: Tested (https://atcoder.jp/contests/abc340/submissions/53206762)
 */

// [0, n] segtree for point query stored value, range increase
// 0 or 1-idx
struct Segtree {
    struct Node {
        // null element:
        ll ps = 0;
    };

    ll L=0, R;
    vector<ll> v;
    vector<Node> tree;

    Segtree(ll n) : R(n), v(n+1), tree(4*(n+1)) {}

    Node merge(Node a, Node b) {
        return Node {
            // merge operation:
            a.ps + b.ps
        };
    }

    void build(ll l, ll r, ll i) {
        if (l == r) {
            tree[i] = Node {
                // leaf element:
                v[l]
            };
        }
        else {
            ll mid = (l+r)/2;
            build(l, mid, 2*i);
            build(mid+1, r, 2*i+1);
            tree[i] = Node{};
        }
    }
    void build() {
        build(L, R, 1);
    }

    void increase(ll val, ll left, ll right, ll l, ll r, ll i) {
        if (right < l or r < left) return;
        else if (left <= l and r <= right) {
            // increase operation
            tree[i].ps += val;
        }
        else {
            ll mid = (l+r)/2;
            increase(val, left, right, l, mid, 2*i);
            increase(val, left, right, mid+1, r, 2*i+1);
        }
    }
    void increase(ll val, ll left, ll right) {
        increase(val, left, right, L, R, 1);
    }
 
    Node query(ll idx, ll l, ll r, ll i) {
        if (l == r) {
            return tree[i];
        }
        else {
            ll mid = (l+r)/2;
            if (idx <= mid) 
                return merge(tree[i], query(idx, l, mid, 2*i));
            else 
                return merge(tree[i], query(idx, mid+1, r, 2*i+1));
        }
    }
    Node query(ll idx) {
        return query(idx, L, R, 1);
    }
};
