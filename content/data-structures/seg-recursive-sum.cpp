/**
 * Author: Wallace
 * Date: 11/02/2024 
 * Description: Basic Recursive Segment Tree for
 * points increase and range sum query.
 * When initializing, choose an appropriate value for n.
 * Time: O(N \log(N)) to build, O(\log(N)) to increase or query
 * Status: Tested {https://cses.fi/problemset/result/8449411/}
 */

// [0, n] segtree for range sum query, point increase
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
 
    void build(ll l, ll r, ll i=1) {
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
            tree[i] = merge(tree[2*i], tree[2*i+1]);
        }
    }
    void build() {
        build(L, R, 1);
    }
 
    void increase(ll idx, ll val, ll l, ll r, ll i) {
        if (l == r) {
            // increase operation:
            tree[i].ps += val;
        }
        else {
            ll mid = (l+r)/2;
            if (idx <= mid) increase(idx, val, l, mid, 2*i);
            else increase(idx, val, mid+1, r, 2*i+1);
            tree[i] = merge(tree[2*i], tree[2*i+1]);
        }
    }
    void increase(ll idx, ll val) {
        increase(idx, val, L, R, 1);
    }

    Node query(ll left, ll right, ll l, ll r, ll i) {
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
    Node query(ll left, ll right) {
        return query(left, right, L, R, 1);
    }
};