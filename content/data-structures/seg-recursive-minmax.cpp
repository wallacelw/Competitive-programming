/**
 * Author: Wallace
 * Date: 20/03/2024 
 * Description: Basic Recursive Segment Tree for
 * point update, range min/max query
 * When initializing, choose an appropriate value for n.
 * Time: O(N \log(N)) to build, O(\log(N)) to update or query
 * Status: Tested {https://atcoder.jp/contests/abl/submissions/51473171}
 */

// [0, n] segtree for point update, range min/max query
// 0 or 1-idx
ll L=0, R;
struct Segtree {

    struct Node {
        // null element:
        ll mn = INF, mx = -INF;
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
            min(a.mn, b.mn),
            max(a.mx, b.mx)
        };
    }
 
    void build(ll l=L, ll r=R, ll i=1 ) {
        if (l == r) {
            tree[i] = Node {
                // leaf element:
                v[l],
                v[l]
            };
        }
        else {
            ll mid = (l+r)/2;
            build(l, mid, 2*i);
            build(mid+1, r, 2*i+1);
            tree[i] = merge(tree[2*i], tree[2*i+1]);
        }
    }
 
    void update(ll idx=1, ll val=0, ll l=L, ll r=R, ll i=1 ) {
        if (l == r) {
            // increase operation:
            tree[i].mn = tree[i].mx = val;
        }
        else {
            ll mid = (l+r)/2;
            if (idx <= mid) update(idx, val, l, mid, 2*i);
            else update(idx, val, mid+1, r, 2*i+1);
            tree[i] = merge(tree[2*i], tree[2*i+1]);
        }
    }
 
    Node query(ll left=L, ll right=R, ll l=L, ll r=R, ll i=1) {
        if (right < l or r < left){
            // null element:
            return Node{};
        }
        else if (left <= l and r <= right) return tree[i]; 
        else{
            ll mid = (l+r)/2;
            return merge(
                query(left, right, l, mid, 2*i), 
                query(left, right, mid+1, r, 2*i+1)
            );
        }
    }
};