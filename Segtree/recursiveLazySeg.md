## Recursive Segtree with Lazy propagation

Lazy Segment Tree with sum/max/min range queries and range increase.

Sum queries with increase sum queries tested and works!
 
**TODO** Range Assignments, test max/min range queries;

```cpp
ll L = 1, R;
struct SegtreeLazy{
    struct Node {
        ll ps = 0;
        ll mn = LLINF;
        ll mx = -LLINF;

        bool operator ==(const Node& b) const {
            return (ps == b.ps) and (mn == b.mn) and (mx == b.mx);
        }
    };

    Node merge(Node a, Node b){
        return Node{
            a.ps + b.ps,
            min(a.mn, b.mn),
            max(a.mx, b.mx)
        };
    }

    vector<Node> tree, lazy;
    vector<ll> v;

    SegtreeLazy() {
        tree.assign(4*(R-L+2), Node{});
        lazy.assign(4*(R-L+2), Node{});
        v.assign((R-L+2), 0);
    }

    void build(ll l=L, ll r=R, ll i=1) {
        if (l == r){ // leaf element
            tree[i] = Node{v[l], v[l], v[l]};
            lazy[i] = Node{};
        }
        else{
            ll mid = (l+r)/2;
            build(l, mid, 2*i);
            build(mid+1, r, 2*i+1);
            tree[i] = merge(tree[2*i], tree[2*i+1]);
            lazy[i] = Node{};
        }
    }

    void propagate(ll l, ll r, ll i){
        if(not (lazy[i] == Node{})) {
            Node tmp = lazy[i];
            tmp.ps *= (r-l+1);
            tree[i] = merge(tree[i], tmp);
            if(l != r){
                lazy[2*i] = merge(lazy[2*i], lazy[i]);
                lazy[2*i+1] = merge(lazy[2*i+1], lazy[i]);
            }
            lazy[i] = Node{};
        }
    }

    // [left, right] = (selected interval for the query)
    // l, r = the variables used for the vertex limits

    // increase function adds 'val' to [left, right]
    void increase(ll left=L, ll right=R, ll val=0, ll l=L, ll r=R, ll i=1){
        propagate(l, r, i);

        if (right < l or r < left) return;

        else if (left <= l and r <= right){
            lazy[i] = Node{val, val, val};
            propagate(l, r, i);
        }

        else{
            ll mid = (l+r)/2;
            increase(left, right, val, l, mid, 2*i);
            increase(left, right, val, mid+1, r, 2*i+1);
            tree[i] = merge(tree[2*i], tree[2*i+1]);
        }
    }

    Node query(ll left=L, ll right=R, ll l=L, ll r=R, ll i=1){
        propagate(l, r, i);

        if (right < l or r < left) return Node{};

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
```