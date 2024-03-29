## Implicit Segtree or Sparse Segtree

Creates vertices only when needed.
Uncreated vertices are considered to have default values.

**TODO** Needs testing!

```cpp
// Remember to set R value !!
ll L=1, R;
struct SegImplicit {
    struct Node{
        ll ps = 0, Lnode = 0, Rnode = 0;
    };
    ll idx = 2; // 1-> root / 0-> zero element
    Node tree[4*MAX];

    ll merge(Node a, Node b){
        return a.ps + b.ps;
    }

    void increase(ll pos, ll x, ll l=L, ll r=R, ll i=1) {
        if (l == r) {
            tree[i].ps += x;
            return;
        }

        ll mid = (l+r)/2;

        if (pos <= mid) {
            if (tree[i].Lnode == 0) tree[i].Lnode = idx++; // new vertex
            increase(pos, x, l, mid, tree[i].Lnode);
        }
        else {
            if (tree[i].Rnode == 0) tree[i].Rnode = idx++;
            increase(pos, x, mid+1, r, tree[i].Rnode);
        }

        tree[i].ps = merge(tree[ tree[i].Lnode ], tree[ tree[i].Rnode ]);
    }

    Node query(ll left, ll right, ll l=L, ll r=R, ll i=1) {
        if (right < l or r < left)
            return Node{};

        if (left <= l and r <= right)
            return tree[i];
            
        ll mid = (l+r)/2;
        Node ansl, ansr;
        if (tree[i].Lnode != 0) ansl = query(left, right, l, mid, tree[i].Lnode);
        if (tree[i].Rnode != 0) ansr = query(left, right, mid+1, r, tree[i].Rnode);

        return Node{merge(ansl, ansr), 0, 0};
    }
};
```