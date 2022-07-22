# Classic Segtree

Data structure that creates parent vertices for a linear array to do faster computation with binary agregation. 

## Código:
```cpp

class SegmentTree {
    public:
        struct node{
            long long psum;
        };

        node tree[4*MAX];
        long long leftLimit;
        long long rightLimit;
        long long v[MAX];

        // requires minimum index and maximum index
        SegmentTree(long long left, long long right) {
            leftLimit = left;
            rightLimit = right;
            memset(v, 0, sizeof(v));
        }

        node merge(node a, node b){
            node tmp;
            // merge operaton:
            tmp.psum = a.psum + b.psum;
            //
            return tmp;
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
```

## Avisos

### Details

**0 or 1-indexed**, depends on the arguments passed on to the constructor 


Uses a **struct node** to define node/vertex properties. *Default:* psum 


Uses a **merge function** to define how to join nodes 


### Parameters

**left** and **right**: parameters that are the range limits for the range query 


**l** and **r**: are auxilary variables used for delimiting a vertex boundaries 


**idx**: index of the leaf node that will be updated 


**val**: value that will be inserted to the idx node 


### Atributes

**Tree**: node array 


**v**: vector that are used for leaf nodes 


### Methods

#### O(n):

**build(l, r, i)**: From **v** vector, constructs Segtree 

#### O(log(N))

**point_update(idx, l, r, i, val)**: updates leaf node with *idx* index to *val* value. No return value 


**range_query(left, right, l, r, i)**: does a range query from *left* to *right* (inclusive) and returns a node with the result 


### Requires
MAX variable 

## Problems

- Range Sum Query, point update
- Range Max/Min Query, point update
- Range Xor Query, point update

# Segtree with Lazy propagation

## Código:

```cpp
class SegmentTreeLazy {
    public:
        struct node{
            long long psum;
        };

        node tree[4*MAX];
        long long lazy[4*MAX];
        long long leftLimit;
        long long rightLimit;
        long long v[MAX];

        SegmentTreeLazy(long long left, long long right) {
            leftLimit = left;
            rightLimit = right;
            memset(lazy, 0, sizeof(lazy));
            memset(v, 0, sizeof(v));
        }

        node merge(node a, node b){
            node tmp;
            // merge operaton:
            tmp.psum = a.psum + b.psum;
            //
            return tmp;
        }

        void build (long long l, long long r, long long i) {
            if (l == r){
                node tmp;
                // leaf element
                tmp.psum = v[l];
                //
                tree[i] = tmp;
                lazy[i] = 0;
            }
            else{
                long long mid = (l+r)/2;
                build(l, mid, 2*i);
                build(mid+1, r, 2*i+1);
                tree[i] = merge(tree[2*i], tree[2*i+1]);
                lazy[i] = 0;
            }
        }
        void range_update(long long left, long long right, long long l, long long r, long long i, long long val){
            if (lazy[i]){
                tree[i].psum += lazy[i] * (r-l+1);
                if (l != r){
                    lazy[2*i] += lazy[i];
                    lazy[2*i+1] += lazy[i];
                }
                lazy[i] = 0;
            }

            if (right < l or r < left) return;
            else if (left <= l and r <= right){
                tree[i].psum += val * (r-l+1);
                if (l != r){
                    lazy[2*i] += val;
                    lazy[2*i+1] += val;
                }
            }
            else{
                long long mid = (l+r)/2;
                range_update(left, right, l, mid, 2*i, val);
                range_update(left, right, mid+1, r, 2*i+1, val);
                tree[i] = merge(tree[2*i], tree[2*i+1]);
            }
        }
        node range_query(long long left, long long right, long long l, long long r, long long i){
            // left/right are the range limits for the update query
            // l / r are the variables used for the vertex limits
            if (lazy[i]){
                tree[i].psum += lazy[i] * (r-l+1);
                if (l != r){
                    lazy[2*i] += lazy[i];
                    lazy[2*i+1] += lazy[i];
                }
                lazy[i] = 0;
            }

            if (right < l or r < left){
                node tmp{0};
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
```

## Avisos

### Details

**0 or 1-indexed**, depends on the arguments passed on to the constructor 


Uses a **struct node** to define node/vertex properties. *Default:* psum 


Uses a **merge function** to define how to join nodes 


### Parameters

**left** and **right**: parameters that are the range limits for the range query 


**l** and **r**: are auxilary variables used for delimiting a vertex boundaries 


**idx**: index of the leaf node that will be updated 


**val**: value that will be inserted to the idx node 


### Atributes

**Tree**: node array 


**v**: vector that are used for leaf nodes 


**Lazy**: array containing lazy updates

### Methods

#### O(n):

**build(l, r, i)**: From **v** vector, constructs Segtree 

#### O(log(N))

**range_update(left, right, l, r, i, val)**: updates all element from *left* to *right* (inclusive) with *val* value. No return value 


**range_query(left, right, l, r, i)**: does a range query from *left* to *right* (inclusive) and returns a node with the result 


### Requires
MAX variable 

## Problems

- Range Sum Query, range update
- Range Max/Min Query, range update
- Range Xor Query, range update