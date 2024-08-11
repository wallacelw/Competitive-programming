/**
 * Author: Wallace, Tiagosf00, LeoRiether
 * Date: 10/08/2024 
 * Description: Seg with PA (Progressao Aritmetica / Arithmetic Progression)
 * When initializing the segmente tree, remeber to choose a proper value for (n=R) and call build()
 * Time: O(N \log(N)) to build, O(\log(N)) to increase or query
 * Status: Tested {https://cses.fi/problemset/result/10152074/}
 */

inline pll operator +(pll a, pll b) {
    return {a.ff + b.ff, a.ss + b.ss};
}

// [0, n] segtree for range sum query, range increase with PA
struct SegtreePA {
    struct Node {
        // correctly initialize default null values:
        ll sum = 0;
    };
    
    ll L=0, R;
    vector<ll> v;
    vector<Node> t;
    vector<pll> lazy; // {x, y} of the expression: x*i + y
    // PA: x = ratio, y = constant
 
    SegtreePA(ll n) : R(n), v(n+1), t(4*(n+1)), lazy(4*(n+1)) {}
 
    Node merge(Node a, Node b) {
        return Node {
            // merge operaton:
            a.sum + b.sum
        };
    }
 
    void build(ll l, ll r, ll i) {
        if (l == r) {
            t[i] = Node {
                // leaf element:
                v[l]
            };
        }
        else {
            ll mid = (l+r)/2;
            build(l, mid, 2*i);
            build(mid+1, r, 2*i+1);
            t[i] = merge(t[2*i], t[2*i+1]);
        }
        lazy[i] = {0, 0};
    }
    void build() {
        build(L, R, 1);
    }
 
    void push(ll l, ll r, ll i) {
        auto [x, y] = lazy[i];
        if (x == 0 and y == 0) return;
        ll len = r-l+1;
        // (l_val + r_val) * len / 2
        Node val{ ((y + y + x*(len-1))*len) / 2 };
        t[i] = merge(t[i], val);
        if (l != r) {
            ll mid = (l+r)/2;
            lazy[2*i] = lazy[2*i] + lazy[i];
            lazy[2*i+1] = lazy[2*i+1] + pll{x, y + x*(mid-l+1)};
        }
        lazy[i] = {0, 0};
    }
 
    void increase(ll x, ll y, ll a, ll b, ll l, ll r, ll i) {
        // PA: x = ratio, y = constant
        // [a, b] are the range limits for the query
        // [l, r] are the internal variables of the t
        push(l, r, i);
        if (b < l or r < a) return;
        else if (a <= l and r <= b) {
            lazy[i] = {x, y};
            push(l, r, i);
            return;
        }
        ll mid = (l+r)/2;
        increase(x, y, a, b, l, mid, 2*i);
        ll ny = y + max( x*( mid-max(a, l) + 1), 0LL);
        increase(x, ny, a, b, mid+1, r, 2*i+1);
        t[i] = merge(t[2*i], t[2*i+1]);
    }
    void increase(ll x, ll y, ll a, ll b) {
        increase(x, y, a, b, L, R, 1);
    }
    
    Node query(ll a, ll b, ll l, ll r, ll i) {
        push(l, r, i);
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