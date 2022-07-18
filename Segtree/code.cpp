struct node{
    long long psum;
};

node merge(node a, node b){
    node tmp;
    // merge operaton:
    tmp.psum = a.psum + b.psum;
    //
    return tmp;
}

class SegmentTree {
    private:
        node tree[4*MAX];
        long long leftLimit;
        long long rightLimit;
    public:
        long long v[MAX];

        // requires minimum index and maximum index
        SegmentTree(long long left, long long right) {
            leftLimit = left;
            rightLimit = right;
            memset(v, 0, sizeof(v));
        }

        void build (long long l, long long r, long long i) {
            if (l == r){
                node tmp;
                // leaf element
                tmp.psum = v[l];
                //
                tree[i] = tmp;
            }
            else{
                long long mid = (l+r)/2;
                build(l, mid, 2*i);
                build(mid+1, r, 2*i+1);
                tree[i] = merge(tree[2*i], tree[2*i+1]);
            }
        }
        void point_update(long long idx, long long l, long long r, long long i, long long val){
            if (l == r){
                // update operation to leaf
                node tmp{val};
                //
                tree[i] = tmp;
            }
            else{
                long long mid = (l+r)/2;
                if (idx <= mid)
                    point_update(idx, l, mid, 2*i, val);
                else
                    point_update(idx, mid+1, r, 2*i+1, val);
                tree[i] = merge(tree[2*i], tree[2*i+1]);
            }
        }
        node range_query(long long left, long long right, long long l, long long r, long long i){
            // left/right are the range limits for the update query
            // l / r are the variables used for the vertex limits
            if (right < l or r < left){
                // null element
                node tmp{0};
                //
                return tmp;
            }
            else if (left <= l and r <= right){
                return tree[i];
            }
            else{
                long long mid = (l+r)/2;
                node ansl = range_query(left, right, l, mid, 2*i);
                node ansr = range_query(left, right, mid+1, r, 2*i+1);
                return merge(ansl, ansr);
            }
        }
};