/**
 * Author: Wallace
 * Date: 10/08/2024
 * Description: Segtree with range sum query, range assignment update, range increase update.
 * Time: O(\log(n)) for each query, O(n \log(n)) to build()
 * Status: Tested (https://cses.fi/problemset/result/10152110/)
*/

// [0, n] segtree for range sum query, range assignment update, range increase update.
struct SegtreeLazy {
    struct Node {
        // correctly initialize default null values:
        ll sum = 0;
    };

    ll L=0, R;
    vector<ll> v;
    vector<Node> t;
    vector<pll> lazy; // {val, type}
    // type = 0 (no pending update); type = 1 (increase); type = 2 (assign)

    SegtreeLazy(ll n) : R(n), v(n+1), t(4*(n+1)), lazy(4*(n+1)) {}

    Node merge(Node a, Node b) {
        return Node{
            a.sum + b.sum
        };
    }

    void build(ll l, ll r, ll i) {
        if (l == r) {
            t[i] = Node{
                v[l]
            };
        }
        else {
            ll mid = (l+r)/2;
            build(l, mid, 2*i);
            build(mid+1, r, 2*i+1);
            t[i] = merge(t[2*i], t[2*i+1]);
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
                t[i].sum += val * (r-l+1);
            }
            else if (type == 2) { // assignment type
                t[i].sum = val * (r-l+1);
            }
            if (l != r) { // push downwards
                for(auto j : {2*i, 2*i+1}) {
                    auto &[val2, type2] = lazy[j];
                    if (type2 == 0) { // child is empty => just replace
                        lazy[j] = lazy[i];
                    }
                    else if (type == type2) { // same type => just push
                        if (type == 1) val2 += val;
                        else val2 = val;
                    }
                    else if (type2 == 1 and type == 2) { // increase then assign
                        lazy[j] = lazy[i]; // just ignore past increasing and only assign
                    }
                    else if (type2 == 2 and type == 1) { // assign then increase
                        val2 += val; // keep the assignment, but increase it
                    }
                }
            }
            lazy[i] = {0, 0};
        }
    }

    // [a, b] are the range limits for the query
    // [l, r] are the internal variables of the t
    void update(ll val, ll type, ll a, ll b, ll l, ll r, ll i) {
        push(l, r, i);
        if (b < l or r < a) return;
        else if (a <= l and r <= b){
            lazy[i] = {val, type};
            push(l, r, i);
            return;
        }
        ll mid = (l+r)/2;
        update(val, type, a, b, l, mid, 2*i);
        update(val, type, a, b, mid+1, r, 2*i+1);
        t[i] = merge(t[2*i], t[2*i+1]);
    }
    void update(ll val, ll type, ll a, ll b) {
        update(val, type, a, b, L, R, 1);
    }

    Node query(ll a, ll b, ll l, ll r, ll i) {
        push(l, r, i);
        if (b < l or r < a) return Node{}; // default null value
        else if (a <= l and r <= b) return t[i];
        ll mid = (l+r)/2;
        return merge(
            query(a, b, l, mid, 2*i),
            query(a, b, mid+1, r, 2*i+1)
        );
    }
    Node query(ll a, ll b) {
        return query(a, b, L, R, 1);
    }
};