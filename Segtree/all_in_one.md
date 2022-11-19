## Segtree with sum, max, min

```cpp
#define int long long // need long long ? 
// !  Initialize N  !
int L = 1, N; // L = 1 = left limit; N = right limit
// 1 - indexed 
class SegmentTree {
    public:
        struct node{
            int psum, mx, mn;
        };

        node merge(node a, node b){
            node tmp;
            // merge operaton:
            tmp.psum = a.psum + b.psum;
            tmp.mx = max(a.mx, b.mx);
            tmp.mn = min(a.mn, b.mn);
            return tmp;
        }

        vector<node> tree;
        vector<int> v;

        SegmentTree() {
            v.assign(N+2, 0);
            tree.assign(N*4 + 10, node{0, 0, 0});
        }

        void build (int l=L, int r=N, int i=1) {
            if (l == r){
                // leaf element
                node tmp{v[l], v[l], v[l]};
                tree[i] = tmp;
            }
            else{
                int mid = (l+r)/2;
                build(l, mid, 2*i);
                build(mid+1, r, 2*i+1);
                tree[i] = merge(tree[2*i], tree[2*i+1]);
            }
        }

        void point_update(int idx=1, int val=0, int l=L, int r=N, int i=1){
            if (l == r){
                // update operation to leaf
                node tmp{val, val, val};
                tree[i] = tmp;
            }
            else{
                int mid = (l+r)/2;
                if (idx <= mid) point_update(idx, val, l, mid, 2*i);
                else point_update(idx, val, mid+1, r, 2*i+1);
                tree[i] = merge(tree[2*i], tree[2*i+1]);
            }
        }
        node range_query(int left=L, int right=N, int l=L, int r=N, int i=1){
            // left/right are the range limits for the update query
            // l / r are the variables used for the vertex limits
            if (right < l or r < left){ // out of bounds
                // null element
                node tmp{0, -INF, INF};
                return tmp;
            }
            else if (left <= l and r <= right){ // contained interval
                return tree[i];
            }
            else{ // partially contained
                int mid = (l+r)/2;
                node ansl = range_query(left, right, l, mid, 2*i);
                node ansr = range_query(left, right, mid+1, r, 2*i+1);
                return merge(ansl, ansr);
            }
        }
};
```