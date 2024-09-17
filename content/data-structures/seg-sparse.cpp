// doesnt work yet
struct Segtree {
    struct Node {
        ll sum = 0;

        ll l = 0, r = 0;
    };

    ll L = 0, R;
    // 0=null, 1=root
    vector<Node> t; 

    Segtree(ll n) : R(n), t(2) {}

    Node merge(Node a, Node b) {
        return Node{a.sum + b.sum};
    }

    void expand(Node &node) {
        node.l = t.size();
        t.pb(Node{});
        node.r = t.size();
        t.pb(Node{});
    }

    void add(ll pos, ll val, ll l, ll r, ll i) {
        if (l == r) {
            t[i].sum += val;
            return;
        }
        ll mid = (l+r)/2;
        expand(t[i]);
        if (pos <= mid)
            add(pos, val, l, mid, t[i].l);
        else
            add(pos, val, mid+1, r, t[i].r);
        t[i] = merge(t[t[i].l], t[t[i].r]);
    }
    void add(ll pos, ll val) {
        add(pos, val, L, R, 1);
    }

    Node query(ll a, ll b, ll l, ll r, ll i) {
        if (b < l or r < b) return Node{};
        if (b <= l and r <= b) return t[i];
        ll mid = (l+r)/2;
        return merge(
            query(a, b, l, mid, t[i].l),
            query(a, b, mid+1, r, t[i].r)
        );
    }
    Node query(ll a, ll b) {
        return query(a, b, L, R, 1);
    }
};

int32_t main() { sws;
    ll n, q; cin >> n >> q;

    vector<ll> x(n+1);
    Segtree st(1e10);

    for(ll i=1; i<=n; i++) {
        cin >> x[i];
        st.add(x[i], 1);
    }

    while(q--) {
        char c; cin >> c;
        if (c == '!') {
            ll pos, val; cin >> pos >> val;
            st.add(x[pos], -1);
            x[pos] = val;
            st.add(x[pos], 1);
        }
        else {
            ll a, b; cin >> a >> b;
            cout << st.query(a, b).sum << endl;
        }
    }
}
