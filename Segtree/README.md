# Classic Segtree

Data structure that creates parent vertices for a linear array to do faster computation with binary agregation. 

![Diagrama](segtree_diagram.png)

## Código:
```cpp
int L = 1, N; // L = 1 = left limit; N = right limit
class SegmentTree {
    public:
        struct node{
            int psum;
        };

        node tree[4*MAX];
        int v[MAX];

        // requires minimum index and maximum index
        SegmentTree() {
            memset(v, 0, sizeof(v));
        }

        node merge(node a, node b){
            node tmp;
            // merge operaton:
            tmp.psum = a.psum + b.psum;
            //
            return tmp;
        }

        void build (int l=L, int r=N, int i=1) {
            if (l == r){
                node tmp;
                // leaf element
                tmp.psum = v[l];
                //
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
                node tmp{val};
                //
                tree[i] = tmp;
            }
            else{
                int mid = (l+r)/2;
                if (idx <= mid)
                    point_update(idx, val, l, mid, 2*i);
                else
                    point_update(idx, val, mid+1, r, 2*i+1);
                tree[i] = merge(tree[2*i], tree[2*i+1]);
            }
        }
        node range_query(int left=L, int right=N, int l=L, int r=N, int i=1){
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
                int mid = (l+r)/2;
                node ansl = range_query(left, right, l, mid, 2*i);
                node ansr = range_query(left, right, mid+1, r, 2*i+1);
                return merge(ansl, ansr);
            }
        }
};
```

## Avisos

### Details

**0 or 1-indexed**, depends on the arguments used as default value


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
ll L=1, N; // L=1=left delimiter; N=right delimiter
class SegmentTreeLazy {
    public:
        struct node{
            int psum = 0;
        };

        node tree[4*MAX];
        int lazy[4*MAX];
        int v[MAX];

        node merge(node a, node b){
            node tmp;
            // merge operaton:
            tmp.psum = a.psum + b.psum;
            //
            return tmp;
        }
        
        SegmentTreeLazy() {
            memset(lazy, 0, sizeof(lazy));
            memset(v, 0, sizeof(v));
        }

        void build (int l=L, int r=N, int i=1) {
            if (l == r){
                node tmp;
                // leaf element
                tmp.psum = v[l];
                //
                tree[i] = tmp;
                lazy[i] = 0;
            }
            else{
                int mid = (l+r)/2;
                build(l, mid, 2*i);
                build(mid+1, r, 2*i+1);
                tree[i] = merge(tree[2*i], tree[2*i+1]);
                lazy[i] = 0;
            }
        }
        void range_update(int left=L, int right=N, int val=0, int l=L, int r=N, int i=1){
            // left/right are the range limits for the update query (can be chosen)
            // l / r are the variables used for the vertex limits
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
                int mid = (l+r)/2;
                range_update(left, right, val, l, mid, 2*i);
                range_update(left, right, val, mid+1, r, 2*i+1);
                tree[i] = merge(tree[2*i], tree[2*i+1]);
            }
        }
        node range_query(int left=L, int right=N, int l=L, int r=N, int i=1){
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
                int mid = (l+r)/2;
                node ansl = range_query(left, right, l, mid, 2*i);
                node ansr = range_query(left, right, mid+1, r, 2*i+1);
                return merge(ansl, ansr);
            }
        }
};
```

## Avisos

### Details

**0 or 1-indexed**, depends on the arguments passed on to the default variables 


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
