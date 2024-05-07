/**
 * Author: Wallace
 * Date: 07/05/2024
 * Description: Segtree with range sum query, range assignment update, range increase update.
 * Time: O(\log(n)) for each query, O(n \log(n)) to build()
 * Status: Tested (https://cses.fi/problemset/result/9193759/)
*/

// [0, n] segtree for range sum query, range assignment update, range increase update.
struct SegtreeLazy {
    struct Node {
        ll ps = 0;
    };

    ll L=0, R;
    vector<ll> v;
    vector<Node> tree;
    vector<pll> lazy; // {val, type}

    SegtreeLazy(ll n) : R(n), v(n+1), tree(4*(n+1)), lazy(4*(n+1)) {}

    Node merge(Node a, Node b) {
        return Node{
            a.ps + b.ps
        };
    }

    void build(ll l, ll r, ll i) {
        if (l == r) {
            tree[i] = Node{
                v[l]
            };
        }
        else {
            ll mid = (l+r)/2;
            build(l, mid, 2*i);
            build(mid+1, r, 2*i+1);
            tree[i] = merge(tree[2*i], tree[2*i+1]);
        }
        lazy[i] = {0, 0};
    }
    void build() {
        build(L, R, 1);
    }

    void push(ll l, ll r, ll i) {
        if (lazy[i].ss) {
            auto [val, type] = lazy[i];
            if (type == 1) { // increase type
                tree[i].ps += val * (r-l+1);
            }
            else if (type == 2) { // assignment type
                tree[i].ps = val * (r-l+1);
            }
            if (l != r) { // push downwards
                for(auto j : {2*i, 2*i+1}) {
                    auto &[val2, type2] = lazy[j];
                    if (type2 == 0) { // empty => just substitute
                        lazy[j] = lazy[i];
                    }
                    else if (type == type2) { // same type => just push
                        if (type == 1) val2 += val;
                        else val2 = val;
                    }
                    else if (type2 == 1 and type == 2) { // increase then assign
                        lazy[j] = lazy[i]; // just ignore increase and only assign
                    }
                    else if (type2 == 2 and type == 1) { // assign then increase
                        val2 += val; // keep the assignment, but increase it
                    }
                }
            }
            lazy[i] = {0, 0};
        }
    }

    void update(ll val, ll type, ll left, ll right, ll l, ll r, ll i) {
        push(l, r, i);
        if (right < l or r < left) return;
        else if (left <= l and r <= right){
            lazy[i] = {val, type};
            push(l, r, i);
        }
        else{
            ll mid = (l+r)/2;
            update(val, type, left, right, l, mid, 2*i);
            update(val, type, left, right, mid+1, r, 2*i+1);
            tree[i] = merge(tree[2*i], tree[2*i+1]);
        }
    }
    void update(ll val, ll type, ll left, ll right) {
        update(val, type, left, right, L, R, 1);
    }

    Node query(ll left, ll right, ll l, ll r, ll i) {
        push(l, r, i);
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
    Node query(ll left, ll right) {
        return query(left, right, L, R, 1);
    }
};