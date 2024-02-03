## Inverted Segtree

**Range_increase** -> using delta encoding

**Point_query** -> adding all values during query transversal

```cpp
// left,right are the range limits for the update query
// l,r are the variables used for the vertex limits
// L = left limit; R = right limit (both inclusive)
// updated 30/01/2024
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
```