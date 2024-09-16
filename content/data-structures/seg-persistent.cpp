/**
 * Author: Wallace
 * Date: 15/09/2024 
 * Description: Persistent Segment Tree, for range sum query, point assignment, point increase
 * It will cause memory leak, but when the process ends, the memory will be released
 * When initializing, choose an appropriate value for (n = R) and call build()
 * Time: O(N \log(N)) to build, O(\log(N)) to update or query
 * Memory: O((N + Q) \log(N)) 
 * Status: Tested {https://cses.fi/problemset/result/10524317/, https://www.spoj.com/problems/MKTHNUM/}
 */


// [0, n] segtree for point assignment/increase update, range sum query
struct Segtree {
    struct Node {
        Node *l, *r;

        ll sum = 0;

        Node(ll val) : l(NULL), r(NULL), sum(val) {}

        // merge operator
        Node(Node *a, Node *b) : l(a), r(b), sum(0) {
            if (l) sum += l->sum;
            if (r) sum += r->sum;
        }
    };

    ll L=0, R;
    vector<ll> v;

    Segtree(ll n) : R(n), v(n+1) {}

    Node* build(ll l, ll r) {
        if (l == r) return new Node(v[l]);
        ll mid = (l+r)/2;
        return new Node(build(l, mid), build(mid+1, r));
    }
    Node* build() {
        return build(L, R);
    }

    ll query(Node *node, ll a, ll b, ll l, ll r) {
        if (b < l or r < a) return 0; // null element
        else if (a <= l and r <= b) return node->sum;
        ll mid = (l+r)/2;
        return (
            query(node->l, a, b, l, mid) + 
            query(node->r, a, b, mid+1, r)
        );
    }
    ll query(Node *node, ll a, ll b) {
        return query(node, a, b, L, R);
    }

    Node* assignment(Node *node, ll pos, ll val, ll l, ll r) {
        if (l == r) return new Node(val);
        ll mid = (l+r)/2;
        if (pos <= mid) {
            return new Node(
                assignment(node->l, pos, val, l, mid),
                node->r
            );
        }
        else {
            return new Node(
                node->l,
                assignment(node->r, pos, val, mid+1, r)
            );
        }
    }
    Node* assignment(Node *node, ll pos, ll val) {
        return assignment(node, pos, val, L, R);
    }

    Node* increase(Node *node, ll pos, ll inc, ll l, ll r) {
        if (l == r) return new Node(node->sum + inc);
        ll mid = (l+r)/2;
        if (pos <= mid) {
            return new Node(
                increase(node->l, pos, inc, l, mid),
                node->r
            );  
        }
        else {
            return new Node(
                node->l,
                increase(node->r, pos, inc, mid+1, r)
            );
        }
    }
    Node* increase(Node *node, ll pos, ll inc) {
        return increase(node, pos, inc, L, R);
    }

    // K-th element in range (a, b], *a and *b are roots
    ll kth(Node *a, Node *b, ll k, ll l, ll r) {
        if (l == r) return l;
        ll mid = (l+r)/2;
        ll left_cnt = b->l->sum - a->l->sum;
        if (k <= left_cnt) {
            return kth(a->l, b->l, k, l, mid);
        }
        else {
            return kth(a->r, b->r, k-left_cnt, mid+1, r);
        }
    }
    ll kth(Node *a, Node *b, ll k) {
        return kth(a, b, k, L, R);
    }
};

int32_t main() { sws;
    ll n, q; cin >> n >> q;

    vector<ll> x(n+1);

    set<ll> unique;
    for(ll i=1; i<=n; i++) {
        cin >> x[i];
        unique.insert(x[i]);
    }

    map<ll, ll> compress, decompress;
    ll idx = 1;
    for(auto elem : unique) {
        decompress[idx] = elem;
        compress[elem] = idx++;
    }

    Segtree st(unique.size());

    vector<Segtree::Node*> root;
    root.pb( st.build() );

    for(ll i=1; i<=n; i++) {
        auto ptr = st.increase(root.back(), compress[x[i]], 1);
        root.pb(ptr);
    }

    while(q--) {
        ll a, b, k; cin >> a >> b >> k;
        cout << decompress[ st.kth(root[a-1], root[b], k) ] << endl;
    }
}