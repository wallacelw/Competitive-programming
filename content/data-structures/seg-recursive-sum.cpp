/**
 * Author: Wallace
 * Date: 10/08/2024 
 * Description: Basic Recursive Segment Tree for
 * points increase and range sum query.
 * When initializing, choose an appropriate value for n = R and call build()
 * Time: O(N \log(N)) to build, O(\log(N)) to increase or query
 * Status: Tested {https://cses.fi/problemset/result/10152034/}
 */

// [0, n] segtree for range sum query, point increase
struct Segtree {
    struct Node {
        // correctly initialize default null values:
        ll sum = 0;
    };
    
    ll L=0, R;
    vector<ll> v;
    vector<Node> t; // tree
    
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
        t[i] = merge(t[2*i], t[2*i+1]);
    }
    void build() {
        build(L, R, 1);
    }
 
    void add(ll pos, ll inc, ll l, ll r, ll i) {
        if (l == r) {
            // add operation:
            t[i].sum += inc;
            return;
        }
        ll mid = (l+r)/2;
        if (pos <= mid) 
            add(pos, inc, l, mid, 2*i);
        else 
            add(pos, inc, mid+1, r, 2*i+1);
        t[i] = merge(t[2*i], t[2*i+1]);
    }
    void add(ll pos, ll inc) {
        add(pos, inc, L, R, 1);
    }
 
    void assign(ll pos, ll val, ll l, ll r, ll i) {
        if (l == r) {
            // assign operation:
            t[i].sum = val;
            return;
        }
        ll mid = (l+r)/2;
        if (pos <= mid) 
            assign(pos, val, l, mid, 2*i);
        else 
            assign(pos, val, mid+1, r, 2*i+1);
        t[i] = merge(t[2*i], t[2*i+1]);
    }
    void assign(ll pos, ll val) {
        assign(pos, val, L, R, 1);
    }
 
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