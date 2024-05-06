/**
 * Author: Wallace
 * Date: 20/03/2024 
 * Description: Basic Inverted Segment Tree for
 * point query stored value, range increase
 * When initializing, choose an appropriate value for n.
 * Time: O(N \log(N)) to build, O(\log{N}) to range increase or point query
 * Status: Tested {https://atcoder.jp/contests/abc340/submissions/51471403}
 */

// [0, n] segtree for point query stored value, range increase
// 0 or 1-idx
ll L=0, R;
struct Segtree {

    struct Node {
        // null element:
        ll ps = 0;
    };
 
    vector<Node> tree;
    vector<ll> v;
    
    Segtree(ll n) {
		R = n;
        v.assign(n+1, 0);
        tree.assign(4*(n+1), Node{});
    }
 
    Node merge(Node a, Node b) {
        return Node {
            // merge operation:
            a.ps + b.ps
        };
    }
 
    void build(ll l=L, ll r=R, ll i=1 ) {
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
 
    void increase(ll left, ll right, ll val=0, ll l=L, ll r=R, ll i=1 ) {
        if (right < l or r < left) {
            return;
        }
        else if (left <= l and r <= right) {
            // increase operation
            tree[i].ps += val;
        }
        else {
            ll mid = (l+r)/2;
            increase(left, right, val, l, mid, 2*i);
            increase(left, right, val, mid+1, r, 2*i+1);
        }
    }
 
    Node query(ll idx, ll l=L, ll r=R, ll i=1) {
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
};