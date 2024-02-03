## Hashing

**Probability of colision:**
= n^2 / (2m)

n = Comparissons
m = mod size

*when using multiple mods*, they multiply: m = m1 * m2

```cpp
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

vector<ll> mods = {
    1000000009,1000000021,1000000033,
    1000000087,1000000093,1000000097,
    1000000103,1000000123,1000000181,
    1000000207,1000000223,1000000241,
    1000000271,1000000289,1000000297
};
const ll P = 31; // can be 53

// s[0]*P^n + s[1]*P^(n-1) + ... + s[n]*P^0
struct Hashing {
    ll n, m; // n = s.size(), m = mods used
    string s;
    vector<vll> p, h;

    Hashing(string &ss, ll mm=1)
        : n(ss.size()), s(ss), m(mm), p(m, vll(n)), h(m, vll(n)) {
        for(ll k=0; k<m; k++) {
            for(ll i=0; i<n; i++)
                p[k][i] = (i ? P*p[k][i-1] : 1) % mods[k];
            for(ll i=0; i<n; i++)
                h[k][i] = (s[i] + P*(i ? h[k][i-1] : 0)) % mods[k];
        }
    }

    ll query(ll l, ll r, ll k=0) { // [l, r] inclusive (0-idx), k = mod index
        ll hash = h[k][r] - (l ? (p[k][r-l+1]*h[k][l-1]) % mods[k] : 0);
        return hash < 0 ? hash + mods[k] : hash;
    }
};

int32_t main() { sws;
    shuffle(mods.begin(), mods.end(), rng);
}
```

### Palindrome Queries

Use the hashing of psum and a segtree

```cpp
// left,right are the range limits for the update query
// l,r are the variables used for the vertex limits
// L = left limit; R = right limit (both inclusive)
#warning remember to update L and R!

ll L, R; 
struct SegmentTree {
    
    struct Node{
        ll val = 0;
    };

    Node merge(Node a, Node b){
        Node tmp;
        // merge operaton:
        tmp.val = (MOD + a.val + b.val) % MOD;
        //
        return tmp;
    }

    vector<Node> tree;
    vector<ll> v;

    SegmentTree() {
        tree.assign(4*(R+1), Node());
        v.assign(R+1, 0);
    }

    void build(ll l=L, ll r=R, ll i=1) {
        if (l == r){
            Node tmp;
            // leaf element
            tmp.val = v[l];
            //
            tree[i] = tmp;
        }
        else{
            ll mid = (l+r)/2;
            build(l, mid, 2*i);
            build(mid+1, r, 2*i+1);
            tree[i] = Node();
        }
    }

    Node query(ll pos, ll l=L, ll r=R, ll i=1){
        if (l == r){
            return tree[i];
        }
        else{
            ll mid = (l+r)/2;
            if (pos <= mid)
                return merge(tree[i], query(pos, l, mid, 2*i));
            else
                return merge(tree[i], query(pos, mid+1, r, 2*i+1));
        }
    }

    void add(ll val, ll left=L, ll right=R, ll l=L, ll r=R, ll i=1){
        if (right < l or r < left){
            return;
        }
        else if (left <= l and r <= right){
            tree[i] = merge(tree[i], Node({val}));
        }
        else{
            ll mid = (l+r)/2;
            add(val, left, right, l, mid, 2*i);
            add(val, left, right, mid+1, r, 2*i+1);
        }
    }
};

int32_t main(){ sws;
    ll n, q; cin >> n >> q;
    string tmp; cin >> tmp;
    string s = "#" + tmp;

    L = 0, R = n+1;

    ll P = 53;
    vector<ll> p1(n+2, 1), p2(n+2, 1);
    vector<ll> h1(n+2, 0), h2(n+2, 0);

    for(ll i=1; i<=n; i++) {
        p1[i] = (p1[i-1] * P) % MOD;
        h1[i] = (h1[i-1] + ((s[i] * p1[i]) % MOD)) % MOD;
    }

    for(ll i=n; i>=1; i--) {
        p2[i] = (p2[i+1] * P) % MOD;
        h2[i] = (h2[i+1] + ((s[i] * p2[i]) % MOD)) % MOD;
    }

    SegmentTree st1, st2;

    st1.v = h1, st2.v = h2;
    st1.build(), st2.build();

    while(q--) {
        ll op; cin >> op;
        if (op == 1) {
            ll i; char c;
            cin >> i >> c;

            st1.add((MOD - (s[i]*p1[i])) % MOD, i, n);
            st2.add((MOD - (s[i]*p2[i])) % MOD, 1, i);

            st1.add((c*p1[i]) % MOD, i, n);
            st2.add((c*p2[i]) % MOD, 1, i);

            s[i] = c;
        }
        else {
            ll l, r; cin >> l >> r;

            ll hash1 = (MOD + st1.query(r).val - st1.query(l-1).val) % MOD;
            ll hash2 = (MOD + st2.query(l).val - st2.query(r+1).val) % MOD;

            ll offset1 = l, offset2 = n+1-r;
            ll diff = abs(offset1 - offset2);
            
            if (offset1 < offset2) {
                hash1 = (hash1 * p1[diff]) % MOD;
            }
            else {
                hash2 = (hash2 * p1[diff]) % MOD;
            }

            if (hash1 == hash2)
                cout << "YES" << endl;
            else    
                cout << "NO" << endl;
        }
    }
}
```