/**
 * Author: Wallace, Tiagosf00, LeoRiether
 * Date: 14/02/2024 
 * Description: Seg with PA (Progressao Aritmetica / Arithmetic Progression)
 * When initializing the segmente tree, remeber to choose the range limits (L, R) and call build()
 * Time: O(N \log{N}) to build, O(\log{N}) to increase or query
 * Status: Tested {https://cses.fi/problemset/result/8475932/}
 */

// [0, n] segtree for range sum query, point increase
ll L=0, R;
struct SegtreePA {

    struct Node {
        // null element:
        ll ps = 0;
    };
 
    vector<Node> tree;
    vector<ll> v;
    vector<pll> lazy; // {x, y} of {x*i + y}
    // x = razao da PA, y = constante

    SegtreePA(ll n) {
		R = n;
        v.assign(n+1, 0);
        tree.assign(4*(n+1), Node{});
        lazy.assign(4*(n+1), pll());
    }
 
    Node merge(Node a, Node b) {
        return Node {
            // merge operaton:
            a.ps + b.ps
        };
    }
    
    inline pll sum(pll a, pll b) {
        return {a.ff+b.ff, a.ss+b.ss};
    }

    void build(ll l=L, ll r=R, ll i=1) {
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

    void prop(ll l=L, ll r=R, ll i=1) {
        auto [x, y] = lazy[i];
        if (x == 0 and y == 0) return;
        ll len = r-l+1;

        // (l_val + r_val) * len / 2
        Node val{ ((y + y + x*(len-1))*len) / 2 };
        tree[i] = merge(tree[i], val);

        if (l != r) {
            ll mid = (l+r)/2;
            lazy[2*i] = sum(lazy[2*i], lazy[i]);
            lazy[2*i+1] = sum(lazy[2*i+1], {x, y + x*(mid-l+1)});
        }

        lazy[i] = {0, 0};
    }

    // left/right are the range limits for the query
    // l / r are the internal variables of the tree
    void increase(ll left, ll right, ll x, ll y, ll l=L, ll r=R, ll i=1 ) {
        prop(l, r, i);
        if (right < l or r < left) return;
        else if (left <= l and r <= right) {
            lazy[i] = {x, y};
            prop(l, r, i);
        }
        else{
            ll mid = (l+r)/2;
            increase(left, right, x, y, l, mid, 2*i);
            ll ny = y + max( x*( mid-max(left, l) + 1), 0LL);
            increase(left, right, x, ny, mid+1, r, 2*i+1);
            tree[i] = merge(tree[2*i], tree[2*i+1]);
        }
    }
 
    Node query(ll left=L, ll right=R, ll l=L, ll r=R, ll i=1) {
        prop(l, r, i);
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
};