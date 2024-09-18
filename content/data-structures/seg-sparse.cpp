/**
 * Author: Wallace
 * Date: 18/09/2024 
 * Description: Sparse Segment Tree, for range sum query, point point increase
 * When initializing, choose an appropriate value for (n, q and mx)
 * Time: O(\log(N)) to update or query
 * Status: Tested {https://cses.fi/problemset/result/10556687/}
 */

// Sparse Segtree that covers [0, mx]
// n = initial vector size, q = number of queries
// point add update, range sum query
struct Segtree {
    struct Node {
        ll l = 0, r = 0;
        ll sum = 0;
    };

    // t[0]=null, t[1]=root
    ll idx = 2, L = 0, R;
    vector<Node> t; 

    Segtree(ll mx, ll n=1e6, ll q=1e6) : R(mx), t((n+q+10)*__lg(2*n+10)) {}

    ll merge(ll a, ll b) {
        return a + b;
    }

    void add(ll pos, ll val, ll l, ll r, ll i) {
        if (l == r) {    
            t[i].sum += val;
            return;
        }
        ll mid = (l+r)/2;
        if (pos <= mid) {
            if (!t[i].l) t[i].l = idx++;
            add(pos, val, l, mid, t[i].l);
        }
        else {
            if (!t[i].r) t[i].r = idx++;
            add(pos, val, mid+1, r, t[i].r);
        }
        t[i].sum = merge(t[t[i].l].sum, t[t[i].r].sum);
    }
    void add(ll pos, ll val) {
        add(pos, val, L, R, 1);
    }

    ll query(ll a, ll b, ll l, ll r, ll i) {
        if (b < l or r < a) return 0;
        if (a <= l and r <= b) return t[i].sum;
        ll mid = (l+r)/2;
        ll ansl = 0, ansr = 0;
        if (t[i].l) ansl = query(a, b, l, mid, t[i].l);
        if (t[i].r) ansr = query(a, b, mid+1, r, t[i].r);
        return merge(ansl, ansr);
    }
    ll query(ll a, ll b) {
        return query(a, b, L, R, 1);
    }
};