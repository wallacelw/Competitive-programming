/**
 * Author: Wallace, Tiagosf00, LeoRiether
 * Date: 14/02/2024 
 * Description: Seg with PA (Progressao Aritmetica / Arithmetic Progression)
 * When initializing the segmente tree, remeber to choose the range limits (L, R) and call build()
 * Time: O(N \log(N)) to build, O(\log(N)) to increase or query
 * Status: Tested {https://cses.fi/problemset/result/9192570/}
 */

inline pll operator +(pll a, pll b) {
    return {a.ff + b.ff, a.ss + b.ss};
}

// [0, n] segtree for range sum query, point increase
struct SegtreePA {
    struct Node {
        // null element:
        ll ps = 0;
    };
    
    ll L=0, R;
    vector<ll> v;
    vector<Node> tree;
    vector<pll> lazy; // {x, y} of the expression: x*i + y
    // x = razao da PA, y = constante
 
    SegtreePA(ll n) : R(n), v(n+1), tree(4*(n+1)), lazy(4*(n+1)) {}
 
    Node merge(Node a, Node b) {
        return Node {
            // merge operaton:
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
            tree[i] = merge(tree[2*i], tree[2*i+1]);
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
        tree[i] = merge(tree[i], val);
        if (l != r) {
            ll mid = (l+r)/2;
            lazy[2*i] = lazy[2*i] + lazy[i];
            lazy[2*i+1] = lazy[2*i+1] + pll{x, y + x*(mid-l+1)};
        }
        lazy[i] = {0, 0};
    }

    void increase(ll x, ll y, ll left, ll right, ll l, ll r, ll i) {
        push(l, r, i);
        if (right < l or r < left) return;
        else if (left <= l and r <= right) {
            lazy[i] = {x, y};
            push(l, r, i);
        }
        else{
            ll mid = (l+r)/2;
            increase(x, y, left, right, l, mid, 2*i);
            ll ny = y + max( x*( mid-max(left, l) + 1), 0LL);
            increase(x, ny, left, right, mid+1, r, 2*i+1);
            tree[i] = merge(tree[2*i], tree[2*i+1]);
        }
    }
    void increase(ll x, ll y, ll left, ll right) {
        increase(x, y, left, right, L, R, 1);
    }
 
    Node query(ll left, ll right, ll l, ll r, ll i) {
        push(l, r, i);
        if (right < l or r < left) {
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