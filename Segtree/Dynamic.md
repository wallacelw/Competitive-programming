## Dynamic Segtree 

Creates vertices only when needed. Stores historical values
**TODO** Needs testing!


```cpp
struct Vertex {
    int arrIdx;
    Vertex *l, *r;
    int sum;
 
    Vertex(int idx,int val) : l(nullptr), r(nullptr), arrIdx(idx),sum(val) {}
    Vertex(int idx, Vertex *l, Vertex *r) : l(l), r(r), sum(0),arrIdx(idx)  {
        if (l) sum += l->sum;
        if (r) sum += r->sum;
    }
};
 
Vertex* build(int idx,int a[], int tl, int tr) {
    if (tl == tr)
        return new Vertex(idx,a[tl]);
    int tm = (tl + tr) / 2;
    return new Vertex(idx,build(idx,a, tl, tm), build(idx,a, tm+1, tr));
}
 
int get(Vertex* v, int tl, int tr, int l, int r) {
    if (l > r)
        return 0;
    if (l == tl && tr == r)
        return v->sum;
    int tm = (tl + tr) / 2;
    return get(v->l, tl, tm, l, min(r, tm))
         + get(v->r, tm+1, tr, max(l, tm+1), r);
}
 
Vertex* update(int idx,Vertex* v, int tl, int tr, int pos, int new_val) {
    if (tl == tr)
        return new Vertex(idx,new_val);
    int tm = (tl + tr) / 2;
    if (pos <= tm)
        return new Vertex(idx,update(idx,v->l, tl, tm, pos, new_val), v->r);
    else
        return new Vertex(idx,v->l, update(idx,v->r, tm+1, tr, pos, new_val));
}

```